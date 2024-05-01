import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

// Java program to demonstrate BufferedReader
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Cliente {
    public static void main(String[] args) throws IOException {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            // Localizar el registro RMI en la máquina donde se ejecuta el servidor principal
            Registry registry = LocateRegistry.getRegistry(1099);
            
            
            // Obtener la referencia remota al objeto del servidor
            ServidorInterface servidor = (ServidorInterface) registry.lookup("Servidor");

            boolean acceso = false;
            String nombre = "";
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            // Registro donante 



            System.out.println("¿Se ha registrado previamente? (S/N):");
            String respuesta = reader.readLine();

            for (int i=0; i<respuesta.length(); i++) {
                System.out.println(respuesta.charAt(i));
            }

            if (respuesta.equalsIgnoreCase("N")) {
                System.out.println("Registrando un nuevo usuario");
                System.out.println("Introduzca su nombre:");
                nombre = reader.readLine();
                System.out.println("Registrando...");
                if(servidor.registrarDonante(nombre)) {
                    acceso = true;
                    System.out.println("Registrado con éxito");
                } else {
                    System.out.println("No se ha podido registrar, ya existe un donante con ese nombre");
                }
            } else if (respuesta.equalsIgnoreCase(respuesta)){
                System.out.println("Inicio de sesión");
                System.out.println("Introduzca su nombre:");
                nombre = reader.readLine();
                if (!servidor.registrarDonante(nombre)) {
                    acceso = true;
                    System.out.println("Inicio de sesión con éxito");
                }
            }

            while (acceso) {
                System.out.println("\n\n¿Qué desea hacer?");
                System.out.println("1. Ver lista de donantes");
                System.out.println("2. Donar");
                System.out.println("3. Ver total donado");
                System.out.println("4. Salir");
                int opcion = Integer.parseInt(reader.readLine());
                switch (opcion) {
                    case 1:
                        System.out.println(servidor.verListaDonantes(nombre));
                        break;
                    case 2:
                        System.out.println("Introduzca la cantidad a donar:");
                        double cantidad = Double.parseDouble(reader.readLine());
                        servidor.donar(nombre, cantidad);
                        break;
                    case 3:

                        double total = servidor.verTotalDonado(nombre);
                        if (total != -1) {
                            System.out.println("Total donado: " + total);
                        } else {
                            System.out.println("No tienes permiso para ver el total donado, recuerde que debe estar registrado y haber donado previamente.");
                        }
                        break;
                    case 4:
                        acceso = false;
                        break;
                    default:
                        System.out.println("Opción no válida");
                        break;
                }
            
            }

        } catch (Exception e) {
            System.err.println("Error en el cliente: " + e.toString());
            e.printStackTrace();
        }
    }
}
