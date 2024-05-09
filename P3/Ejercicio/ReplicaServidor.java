
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;
enum Estado {
    LIBRE, SOLICITANDO, EN_SECCION_CRITICA
}

public class ReplicaServidor extends UnicastRemoteObject implements ServidorInterface {
    private ArrayList<ServidorInterface> replicas;
    private int id;

    private long tiempoInicial;

    private Estado estado;
    
    private Map<String, Double> listaDonantes;
    private double dineroDonado;

    public ReplicaServidor(int id) throws RemoteException {
        this.replicas = new ArrayList<>();
        this.id = id;
        this.tiempoInicial = System.currentTimeMillis(); // Tiempo en milisegundos
        this.listaDonantes = new HashMap<>();
        this.dineroDonado = 0;
        this.estado = Estado.LIBRE;
    }

    public long obtenerTiempoTranscurrido() {
        return System.currentTimeMillis() - tiempoInicial;
    }

    public void addReplica(ServidorInterface replicaServidor) {
        this.replicas.add(replicaServidor);
    }

    @Override
    public boolean registrarDonante(String nombre) throws RemoteException {      
        System.out.println("Proceso de registrar donante " + nombre + " en servidor " + this.id);  
        if (solicitarSeccionCritica()) {
            
            System.out.println("Buscando donante " + nombre + " en servidores");
            // Comprobar si el nombre se encuentra en algun servidor
            for (int i=0; i < replicas.size(); i++) {
                for(int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                    if(replicas.get(i).getListaDonantes().containsKey(nombre)) {
                        liberarSeccionCritica();
                        return false;
                    }
                }
            }

            // Redirigir la petición a los demás servidores en búsqueda del que menos donantes tenga

            int minDonantes = Integer.MAX_VALUE;
            int numDonantes;
            int idMinDonantes = -1;
            for (int i=0; i<replicas.size(); i++) {
                numDonantes = replicas.get(i).getListaDonantes().size();
                if (numDonantes < minDonantes) {
                    minDonantes = numDonantes;
                    idMinDonantes = i;
                }
            }

            if (idMinDonantes != -1) {
                replicas.get(idMinDonantes).addDonante(nombre);
            }

            liberarSeccionCritica();
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void addDonante(String nombre) throws RemoteException {
        listaDonantes.put(nombre, 0.0);
    }


    @Override
    public Map<String, Double> getListaDonantes() throws RemoteException {
        return listaDonantes;
    }

    @Override
    public String mostrarDonantes(String nombre) throws RemoteException {
        System.out.println("Mostrando donantes");
        if (solicitarSeccionCritica()) {

            boolean permisos = false;

            // Comprobar si el nombre se encuentra en algun servidor para conceder permisos
            if (nombre != null) {
                for (int i=0; i<replicas.size(); i++) {
                    for (int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                        if (replicas.get(i).getListaDonantes().containsKey(nombre)) {
                            //Además se comprueba si ha donado algo para dar permisos
                            if (replicas.get(i).getListaDonantes().get(nombre) > 0.0) permisos = true;
                            else permisos = false;
                            break;
                        }
                    }
                }
            }

            if (!permisos) {
                liberarSeccionCritica();
                return "No tienes permisos para ver los donantes, recuerda registrarte primero y donar algo";
            }

            String resultado = "Lista de donantes: \n";
            
            for (int i=0; i<replicas.size(); i++) {
                for (String nombreDonante : replicas.get(i).getListaDonantes().keySet()) {
                    resultado += nombreDonante + " de la réplica " + i + "\n";
                }
            }
            liberarSeccionCritica();
            return resultado;
        } else {
            return "";
        }
    }

    @Override
    public boolean donacion(String nombre, double cantidad) throws RemoteException {
        System.out.println("Proceso de donacion de" + nombre + " de cantidad " + cantidad + " en servidor " + this.id);
        if (solicitarSeccionCritica()) {
            boolean permisos = false;
            int idServidor = -1;

            // Comprobar si el nombre se encuentra en algun servidor para conceder permisos
            if (nombre != null) {
                for (int i=0; i<replicas.size(); i++) {
                    for (int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                        if (replicas.get(i).getListaDonantes().containsKey(nombre)) {
                            permisos = true;
                            idServidor = i;
                            break;
                        }
                    }
                }
            }

            if (!permisos) {
                liberarSeccionCritica();
                return false;
            }

            if (idServidor != -1) {
                replicas.get(idServidor).donar(nombre, cantidad);
            }

            liberarSeccionCritica();
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void donar(String nombre, double cantidad) throws RemoteException {
        this.listaDonantes.put(nombre, this.listaDonantes.get(nombre) + cantidad);
        dineroDonado += cantidad;
    }

    
    @Override
    public String mostrarTotalDonado(String nombre) throws RemoteException {
        System.out.println("Proceso de ver total donado en servidor " + this.id);
        
        if (solicitarSeccionCritica()) {
            boolean permisos = false;
            for (int i=0; i<replicas.size(); i++) {
                for (int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                    if (replicas.get(i).getListaDonantes().containsKey(nombre)) {
                        //Además se comprueba si ha donado algo para dar permisos
                        if (replicas.get(i).getListaDonantes().get(nombre) > 0.0) permisos = true;
                        else permisos = false;
                        break;
                    }
                }
            }

            if (!permisos) {
                liberarSeccionCritica();
                return "No tienes permisos para ver el total donado, recuerda registrarte primero y donar algo";
            }

            String resultado = "";
            int dineroTotal = 0;
            for (int i=0; i<replicas.size(); i++) {
                dineroTotal += replicas.get(i).getDineroDonado();
            }

            resultado = "El total donado es: " + dineroTotal;
            liberarSeccionCritica();
            return resultado;
        } else {
            return "";
        }
    }
    
    @Override
    public double getDineroDonado() throws RemoteException {
        return this.dineroDonado;
    }

    @Override
    public boolean eliminarDonante(String nombre) throws RemoteException {
        System.out.println("Proceso de eliminar donante " + nombre + " en servidor " + this.id);
        if (solicitarSeccionCritica()) {
            boolean permisos = false;
            int idServidor = -1;

            // Comprobar si el nombre se encuentra en algun servidor para conceder permisos
            if (nombre != null) {
                for (int i=0; i<replicas.size(); i++) {
                    for (int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                        if (replicas.get(i).getListaDonantes().containsKey(nombre)) {
                            permisos = true;
                            idServidor = i;
                            break;
                        }
                    }
                }
            }

            if (!permisos) {
                liberarSeccionCritica();
                return false;
            }

            if (idServidor != -1) {
                replicas.get(idServidor).removeDonante(nombre);
            }

            liberarSeccionCritica();
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void removeDonante(String nombre) throws RemoteException {
        this.listaDonantes.remove(nombre);
    }

    @Override
    public String top5Donantes(String nombre) throws RemoteException {
        System.out.println("Proceso de ver top 5 donantes en servidor " + this.id);
        if (solicitarSeccionCritica()) {
            boolean permisos = false;
            for (int i=0; i<replicas.size(); i++) {
                for (int j=0; j<replicas.get(i).getListaDonantes().size(); j++) {
                    if (replicas.get(i).getListaDonantes().containsKey(nombre)) {
                        //Además se comprueba si ha donado algo para dar permisos
                        if (replicas.get(i).getListaDonantes().get(nombre) > 0.0) permisos = true;
                        else permisos = false;
                        break;
                    }
                }
            }

            if (!permisos) {
                liberarSeccionCritica();
                return "No tienes permisos para ver el top 5 de donantes, recuerda registrarte primero y donar algo";
            }

            //Añadir donantes de todas las réplicas
            String resultado = "";
            Map<String, Double> donantes = new HashMap<>();
            for (int i=0; i<replicas.size(); i++) {
                donantes.putAll(replicas.get(i).getListaDonantes());
            }

            // Collections.sort para ordenar una lista creada a partir del map de donantes
            
            List<Map.Entry<String,Double>> list = new ArrayList<>(donantes.entrySet());
            
            Collections.sort(list, new Comparator<Map.Entry<String,Double>>() {
                public int compare(Map.Entry<String, Double> o1, Map.Entry<String, Double> o2) {
                    return o2.getValue().compareTo(o1.getValue());
                }
            });

            resultado = "Top 5 donantes: \n";

            for (int i=0; i<5; i++) {
                if (i >= list.size()) break;
                resultado += list.get(i).getKey() + " con " + list.get(i).getValue() + "\n";
            }


            liberarSeccionCritica();
            return resultado;
        } else {
            return "";
        }
    }

    @Override
    public boolean solicitarSeccionCritica() throws RemoteException {
        this.estado = Estado.SOLICITANDO;
        long tiempo = obtenerTiempoTranscurrido();
        boolean resultado = true;
        for (int i=0; i<replicas.size(); i++) {
            if (i == this.id) continue;
            resultado = replicas.get(i).recibirSolicitudSeccionCritica(tiempo, this.id);
            if (!resultado) {
                return false;
            }
        }
        this.estado = Estado.EN_SECCION_CRITICA;
        return true;
    }

    @Override
    public boolean recibirSolicitudSeccionCritica(long tiempoRecibido, int idRecibido) {

        long tiempo = obtenerTiempoTranscurrido();
        if (this.estado == Estado.EN_SECCION_CRITICA || (this.estado == Estado.SOLICITANDO && tiempo < tiempoRecibido)) {
            return false;
        } else {
            return true;
        }
    }

    @Override
    public void liberarSeccionCritica() throws RemoteException {
        this.estado = Estado.LIBRE;
    }

    public static void main (String[] args) throws RemoteException{

        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            
            if (args.length != 1) {
                System.out.println("Uso: ReplicaServidor <número réplicas>");
                System.exit(0);
            }

            // Crear registro
            LocateRegistry.createRegistry(1099);
            Registry registry = LocateRegistry.getRegistry(1099);
            
            // Crear réplicas
            int numReplicas = Integer.parseInt(args[0]);

            ArrayList<ReplicaServidor> replicas = new ArrayList<>();

            for (int i=0; i<numReplicas; i++) {
                replicas.add(new ReplicaServidor(i));
            }


            // Registrar replicas

            for (int i=0; i<numReplicas; i++) {
                registry.rebind("Replica" + (i), replicas.get(i));
            }

            // Ligar replicas

            ArrayList<ServidorInterface> stubs = new ArrayList<>();
            for (int i=0; i<numReplicas; i++) {
                stubs.add((ServidorInterface) registry.lookup("Replica" + i));
            }
    
            // Añadir replicas

            for (int i=0; i<numReplicas; i++) {
                for (int j=0; j<numReplicas; j++) {
                    replicas.get(i).addReplica(stubs.get(j));
                }
            }
            
        } catch (Exception e) {
            System.err.println("Servidor exception:");
            e.printStackTrace();
        }
    }
}
