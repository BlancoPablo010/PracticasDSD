
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.*;
import java.util.ArrayList;


public class Servidor extends UnicastRemoteObject implements ServidorInterface {
    private ArrayList<TuplaDonante> listaDonantes;
    private ServidorInterface replicaServidor1;
    private ServidorInterface replicaServidor2;

    public Servidor(ServidorInterface replicaServidor1, ServidorInterface replicaServidor2) throws RemoteException {
        this.listaDonantes = new ArrayList<>();
        this.replicaServidor1 = replicaServidor1;
        this.replicaServidor2 = replicaServidor2;
    }

    @Override
    public boolean registrarDonante(String nombre) throws RemoteException {
        System.out.println("Registrando donante: " + nombre);

        // Se verifica si el donante ya está registrado, si lo está se devuelve false
        for (TuplaDonante donante : listaDonantes) {
            if (donante.getNombre().equals(nombre)) {
                System.out.println("El donante ya está registrado");
                return false;
            }
        }

        int donantesRegistrados1 = replicaServidor1.getNumDonantesRegistrados();
        int donantesRegistrados2 = replicaServidor2.getNumDonantesRegistrados();


        if(donantesRegistrados1 < donantesRegistrados2) {
            if (replicaServidor1.registrarDonante(nombre)) {
                listaDonantes.add(new TuplaDonante(nombre,1,0));
                System.out.println("Donante registrado en el servidor 1");
                return true;
            } else {
                System.err.println("Error al registrar donante en el servidor 1");
                return false;
            }
        } else {
            if(replicaServidor2.registrarDonante(nombre)) {
                listaDonantes.add(new TuplaDonante(nombre,2,0));
                System.out.println("Donante registrado en el servidor 2");
                return true;
            } else {
                System.err.println("Error al registrar donante en el servidor 2");
                return false;
            }
        }
    }

    @Override 
    public int getNumDonantesRegistrados() throws RemoteException {
        return replicaServidor1.getNumDonantesRegistrados() + replicaServidor2.getNumDonantesRegistrados();
    }

    @Override
    public String verListaDonantes(String nombre) throws RemoteException {
        System.out.println("Viendo lista de donantes desde el perfil de " + nombre);
        String lista = "";
        boolean permiso = false;
        for (TuplaDonante donante : listaDonantes) {
            if (donante.getNombre().equals(nombre) && donante.getDonado() > 0){
                permiso = true;
                break;
            }
        }

        if (permiso) {
            for (TuplaDonante donante : listaDonantes) {
                lista += donante.getNombre() + "\n";
            }
        } else {
            lista = "No tienes permiso para ver la lista de donantes, recuerde que debe estar registrado y haber donado previamente.";
        }
        return lista;
    }

    @Override
    public void donar(String nombre, double cantidad) throws RemoteException {
        System.out.println("Donando " + cantidad + " desde el perfil de " + nombre);
        for (TuplaDonante donante : listaDonantes) {
            if (donante.getNombre().equals(nombre)){
                if (donante.getServidor() == 1) {
                    replicaServidor1.donar(nombre, cantidad);
                    donante.setDonado(donante.getDonado() + cantidad);
                } else {
                    replicaServidor2.donar(nombre, cantidad);
                    donante.setDonado(donante.getDonado() + cantidad);
                }
                break;
            }
        }
    }

    @Override 
    public double verTotalDonado(String nombre) throws RemoteException {
        System.out.println("Viendo total donado desde el perfil de " + nombre);
        double total = 0;
        for (TuplaDonante donante : listaDonantes) {
            if (donante.getNombre().equals(nombre) && donante.getDonado() > 0){
                total+= replicaServidor1.verTotalDonado(nombre);
                total+= replicaServidor2.verTotalDonado(nombre);
                break;
            } else {
                System.out.println("No tienes permiso para ver el total donado, recuerde que debe estar registrado y haber donado previamente.");
                return -1;
            }
        }
        return total;
    }

    public static void main(String[] args) throws NotBoundException {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            LocateRegistry.createRegistry(1099);
            LocateRegistry.createRegistry(1100);
            LocateRegistry.createRegistry(1101);
            Registry registryServidor = java.rmi.registry.LocateRegistry.getRegistry(1099);
            Registry registryReplica1 = java.rmi.registry.LocateRegistry.getRegistry(1100);
            Registry registryReplica2 = java.rmi.registry.LocateRegistry.getRegistry(1101);
            ReplicaServidor1 replicaServ1 = new ReplicaServidor1();
            ReplicaServidor2 replicaServ2 = new ReplicaServidor2();

            registryReplica1.rebind("ReplicaServidor1", replicaServ1);
            registryReplica2.rebind("ReplicaServidor2", replicaServ2);

            ServidorInterface replicaServidor1 = (ServidorInterface) registryReplica1.lookup("ReplicaServidor1");
            ServidorInterface replicaServidor2 = (ServidorInterface) registryReplica2.lookup("ReplicaServidor2");

            Servidor servidor = new Servidor(replicaServidor1, replicaServidor2);
            registryServidor.rebind("Servidor", servidor);

            System.out.println("Servidor lanzado en el registro con nombre Servidor y puerto 1099");
        } catch (RemoteException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
