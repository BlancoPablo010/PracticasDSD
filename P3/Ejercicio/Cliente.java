import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;

// Java program to demonstrate BufferedReader
import java.io.IOException;

public class Cliente {
    public static void main(String[] args) throws IOException {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {

            if (args.length != 1) {
                System.out.println("Uso: Cliente <número réplicas>, asegúrese de que tenga el mismo o menos número de réplicas que el servidor principal");
                System.exit(0);
            }
            // Localizar el registro RMI en la máquina donde se ejecuta el servidor principal
            System.out.println("Localizando el registro RMI en el servidor principal");
            Registry registry = LocateRegistry.getRegistry(1099);
            
            
            System.out.println("Localizando las replicas");
            // Obtener la referencia remota al objeto del servidor

            int numReplicas = Integer.parseInt(args[0]);

            ArrayList<ServidorInterface> replicas = new ArrayList<ServidorInterface>();

            for (int i = 0; i < numReplicas; i++) {
                replicas.add((ServidorInterface) registry.lookup("Replica" + i));
            }

            int replica = 0;

            boolean salir = true;

            while (salir) {
                System.out.println("1. Elegir réplica (elegida actualmente: " + replica + ")");
                System.out.println("2. Registrar donante");
                System.out.println("3. Eliminar donante");
                System.out.println("4. Donar");
                System.out.println("5. Ver total donado");
                System.out.println("6. Ver lista de donantes");
                System.out.println("7. Ver top 5 de donantes");
                System.out.println("8. Salir");

                int opcion = Integer.parseInt(System.console().readLine());

                switch (opcion) {
                    case 1:
                        System.out.println("Elegir réplica(0-" + (numReplicas - 1) + ") (actual: " + replica + ")");
                        replica = Integer.parseInt(System.console().readLine());
                        if (replica < 0 || replica > numReplicas) {
                            System.out.println("Réplica no válida");
                            salir = false;
                        }
                        break;
                    case 2:
                        System.out.println("Introduce el nombre del donante");
                        String nombre = System.console().readLine();
                        if (replicas.get(replica).registrarDonante(nombre)) {
                            System.out.println("Donante registrado");
                        } else {
                            System.out.println("Donante no registrado, ya existe");
                        }
                        break;
                    case 3:
                        System.out.println("Introduce el nombre del donante");
                        nombre = System.console().readLine();
                        if (replicas.get(replica).eliminarDonante(nombre)) {
                            System.out.println("Donante eliminado");
                        } else {
                            System.out.println("Donante no eliminado, no se ha encontrado");
                        }
                        break;
                    case 4:
                        System.out.println("Introduce el nombre del donante");
                        nombre = System.console().readLine();
                        System.out.println("Introduce la cantidad a donar");
                        double cantidad = Double.parseDouble(System.console().readLine());
                        if (replicas.get(replica).donacion(nombre, cantidad)) {
                            System.out.println("Donación realizada");
                        } else {
                            System.out.println("Donación no realizada, no se ha encontrado el donante");
                        }
                        break;
                    case 5:
                        System.out.println("Introduce el nombre del donante");
                        nombre = System.console().readLine();
                        System.out.println(replicas.get(replica).mostrarTotalDonado(nombre));
                        break;
                    case 6:
                        System.out.println("Introduce el nombre del donante");
                        nombre = System.console().readLine();
                        System.out.println(replicas.get(replica).mostrarDonantes(nombre));
                        break;
                    case 7:
                        System.out.println("Introduce el nombre del donante");
                        nombre = System.console().readLine();
                        System.out.println(replicas.get(replica).top5Donantes(nombre));
                        break;
                    case 8:
                        salir = false;
                        break;
                    default:
                        break;
                }

            }

        } catch (Exception e) {
            System.err.println("Error en el cliente: " + e.toString());
            e.printStackTrace();
        }
    }
}
