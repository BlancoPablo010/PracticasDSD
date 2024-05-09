import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;

public interface ServidorInterface extends Remote {

    /**
     * Método que solicita la sección crítica
     * @return true si se ha podido solicitar la sección crítica
     * @return false si no se ha podido solicitar la sección crítica
     * @throws RemoteException
     */
    public boolean solicitarSeccionCritica() throws RemoteException;

    /**
     * Método que recibe la solicitud de la sección crítica
     * @param tiempo 
     * @param id
     * @return true si decide que el solicitante de la sección crítica puede entrar
     * @return false si decide que el solicitante de la sección crítica no puede entrar
     * @throws RemoteException
     */
    public boolean recibirSolicitudSeccionCritica(long tiempo, int id) throws RemoteException; 

    /**
     * Método que libera la sección crítica
     * @throws RemoteException
     */
    public void liberarSeccionCritica() throws RemoteException;


    /**
     * Método que registra un donante
     * @param nombre nombre del donante
     * @return true si se ha podido registrar el donante
     * @return false si no se ha podido registrar el donante
     * @throws RemoteException
     */
    public boolean registrarDonante(String nombre) throws RemoteException;

    /**
     * Método que añade un donante, llamado dentro de registrarDonante
     * @param nombre
     * @throws RemoteException
     */
    public void addDonante(String nombre) throws RemoteException;
    
    /**
     * Método que devuelve la lista de donantes
     * @return Map<String, Double> lista de donantes con sus nombres y sus cantidades donadas
     * @throws RemoteException
     */
    public Map<String, Double> getListaDonantes() throws RemoteException;

    /**
     * Método que muestra la lista de donantes y al servidor replicado que pertenece cada uno
     * @param nombre nombre del donante para comprobar si tiene permisos para este método
     * @return String lista de donantes con sus nombres
     * @throws RemoteException
     */
    public String mostrarDonantes(String nombre) throws RemoteException;

    /**
     * Método que realiza una donación
     * @param nombre nombre del donante
     * @param cantidad cantidad donada
     * @return true si se ha podido realizar la donación
     * @return false si no se ha podido realizar la donación
     * @throws RemoteException
     */
    public boolean donacion(String nombre, double cantidad) throws RemoteException;

    /**
     * Método que añade una donación, llamado dentro de donacion
     * @param nombre
     * @param cantidad
     * @throws RemoteException
     */
    public void donar(String nombre, double cantidad) throws RemoteException;

    /**
     * Método que muestra el total donado de todas las réplicas
     * @param nombre nombre del donante para comprobar si tiene permisos para este método
     * @return cadena de texto con el total donado
     * @throws RemoteException
     */
    public String mostrarTotalDonado(String nombre) throws RemoteException;

    /**
     * Método que devuelve cada dinero Donado de cada réplica
     * @return dinero donado en cada réplica
     * @throws RemoteException
     */
    public double getDineroDonado() throws RemoteException;

    /**
     * Método que elimina un donante, si existe
     * @param nombre nombre del donante a eliminar
     * @return true si se ha podido eliminar el donante
     * @return false si no se ha podido eliminar el donante
     * @throws RemoteException
     */

    public boolean eliminarDonante(String nombre) throws RemoteException;


    /**
     * Método que elimina un donante, llamado dentro de eliminarDonante
     * @param nombre
     * @throws RemoteException
     */
    public void removeDonante(String nombre) throws RemoteException;


    /**
     * Método que devuelve una lista con el top 5 de donantes de todas las réplicas
     * @param nombre nombre del donante para comprobar si tiene permisos para este método
     * @return top 5 de donantes
     * @throws RemoteException
     *
     */
    public String top5Donantes(String nombre) throws RemoteException;
}