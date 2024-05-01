import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ServidorInterface extends Remote {

    public boolean registrarDonante(String nombre) throws RemoteException;
    public int getNumDonantesRegistrados() throws RemoteException;

    public String verListaDonantes(String nombre) throws RemoteException;

    public void donar(String nombre, double cantidad) throws RemoteException;

    public double verTotalDonado(String nombre) throws RemoteException;
}