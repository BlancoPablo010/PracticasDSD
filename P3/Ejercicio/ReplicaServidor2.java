
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;


public class ReplicaServidor2 extends UnicastRemoteObject implements ServidorInterface {
    private ArrayList<String> listaDonantes;

    private double totalDonado;

    public ReplicaServidor2() throws RemoteException {
        listaDonantes = new ArrayList<>();
        totalDonado = 0;
    }

    @Override
    public boolean registrarDonante(String nombre) throws RemoteException {
        listaDonantes.add(nombre);
        return true;
    }

    @Override
    public int getNumDonantesRegistrados() {
        return listaDonantes.size();
    }

    @Override 
    public String verListaDonantes(String nombre) throws RemoteException {
        String lista = "";
        for (String donante : listaDonantes) {
            lista += donante + "\n";
        }
        return lista;
    }

    @Override
    public void donar(String nombre, double cantidad) throws RemoteException {
        totalDonado += cantidad;
    }

    @Override
    public double verTotalDonado(String nombre) throws RemoteException {
        return totalDonado;
    }

    public static void main(String[] args) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            ReplicaServidor2 servidor = new ReplicaServidor2();
            java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(1099);
            registry.rebind("ReplicaServidor2", servidor);
            System.out.println("ReplicaServidor2 lanzado en el registro con nombre ReplicaServidor2 y puerto 1099");
        } catch (RemoteException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
