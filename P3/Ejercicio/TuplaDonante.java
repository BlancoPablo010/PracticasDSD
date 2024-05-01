/**
 * Clase que representa una tupla de donante.
 * Primer atributo: nombre del donante.
 * Segundo atributo: servidor al que pertenece el donante.
 */

public class TuplaDonante {
    private String nombre;
    private int servidor;
    private double donado;

    public TuplaDonante(String nombre, int servidor, double donado) {
        this.nombre = nombre;
        this.servidor = servidor;
        this.donado = donado;
    }

    public String getNombre() {
        return nombre;
    }

    public double getServidor() {
        return servidor;
    }

    public double getDonado() {
        return donado;
    }

    public void setDonado(double donado) {
        this.donado = donado;
    }
}