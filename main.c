#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nombre[30];
    float precio;
}tproducto;

void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void resetear()
{
    FILE *arch;
    arch = fopen("productos.dat", "wb");
    if (arch == NULL){
        exit(1);
    }
    fclose(arch);
    continuar();
}

void cargar()
{
    FILE *arch;
    arch= fopen("productos.dat", "ab");
    if (arch==NULL){
        exit(1);
    }
    tproducto producto;
    printf("\nIngrese el codigo");
    scanf("%i", &producto.codigo);
    fflush(stdin);
    printf("\nIngrese el nombre");
    scanf("%s",&producto.nombre);
    printf("\nIngrese el precio");
    scanf("%f", &producto.precio);
    fwrite(&producto, sizeof (tproducto),1, arch);
    fclose(arch);
    continuar();
}

void lista()
{
    FILE *arch;
    arch= fopen("productos.dat", "rb");
    if (arch==NULL){
        exit(1);
    }
    tproducto producto;
    fread(&producto,sizeof(tproducto),1,arch);
    while(!feof(arch))
    {
        printf("\t%i \t%s \t $%0.2f \n", producto.codigo,producto.nombre,producto.precio);
        fread(&producto, sizeof(tproducto),1,arch);
    }
    fclose(arch);
    continuar();
}

void buscar()
{
    FILE *arch;
    arch= fopen("productos.dat", "rb");
    if (arch==NULL){
        exit(1);
    }
    printf("Ingrese el codigo para buscar el modelo de papel");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe=0;
    fread(&producto,sizeof(tproducto),1,arch);
    while(!feof(arch))
    {
        if(cod==producto.codigo)
        {
            printf("\tCodigo/Nombre/Precio\n");
            printf("\t%i \t %s \t $%0.2f\n", producto.codigo, producto.nombre, producto.precio);
            fread(&producto, sizeof(tproducto), 1, arch);
            existe=1;
            break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0){
        printf("no existe ese codigo\n");
    }
    fclose(arch);
    continuar();
}

void modificarPrecio() {
    FILE *arch;
    arch = fopen("productos.dat", "r+b");
    if (arch == NULL) {
        exit(1);
    }
    printf("ingrese el codigo del producto que quieres modificar\n");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe = 0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while (!feof(arch)) {
        if (cod == producto.codigo) {
            printf("\tCodigo  /  Nombre  /  Precio\n");
            printf("\t%i \t %s \t $%0.2f\n", producto.codigo, producto.nombre, producto.precio);
            printf("ingrese nuevo precio\n");
            scanf("%f", &producto.precio);
            int pos = ftell(arch) - sizeof(tproducto);
            fseek(arch, pos, SEEK_SET);
            fwrite(&producto, sizeof(tproducto), 1, arch);
            printf("Se modifico el precio del producto\n");
            existe = 1;
            break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe == 0) {
        printf("No existe un codigo asi");
    }
    fclose(arch);
    continuar();
}

void modificarNombre() {
    FILE *arch;
    arch = fopen("productos.dat", "r+b");
    if (arch == NULL) {
        exit(1);
    }
    printf("ingrese el codigo del producto que quieres modificar\n");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe = 0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while (!feof(arch)) {
        if (cod == producto.codigo) {
            printf("\tCodigo  /  Nombre  /  Precio\n");
            printf("\t%i \t %s \t $%0.2f\n", producto.codigo, producto.nombre, producto.precio);
            printf("ingrese nuevo nombre\n");
            scanf("%s",&producto.nombre);
            int pos = ftell(arch) - sizeof(tproducto);
            fseek(arch, pos, SEEK_SET);
            fwrite(&producto, sizeof(tproducto), 1, arch);
            printf("Se modifico el nombre del producto\n");
            existe = 1;
            break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe == 0) {
        printf("No existe un codigo asi");
    }
    fclose(arch);
    continuar();
}

void modificarCodigo() {
    FILE *arch;
    arch = fopen("productos.dat", "r+b");
    if (arch == NULL) {
        exit(1);
    }
    printf("ingrese el codigo del producto que quieres modificar \n");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe = 0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while (!feof(arch)) {
        if (cod == producto.codigo) {
            printf("\tCodigo  /  Nombre  /  Precio\n");
            printf("\t%i \t %s \t $%0.2f\n", producto.codigo, producto.nombre, producto.precio);
            printf("ingrese nuevo codigo\n");
            scanf("%i", &producto.codigo);
            int pos = ftell(arch) - sizeof(tproducto);
            fseek(arch, pos, SEEK_SET);
            fwrite(&producto, sizeof(tproducto), 1, arch);
            printf("Se modifico el codigo del producto\n");
            existe = 1;
            break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe == 0) {
        printf("No existe un codigo asi");
    }
    fclose(arch);
    continuar();
}

void decisionModificacion()
{
    int decision;
    printf("Que quieres modificar?(1.Codigo/2.Nombre/3.Precio)");
    scanf("%i",&decision);

    if(decision==1){
        modificarCodigo();
    }
    else if(decision==2){
        modificarNombre();
    }
    else if (decision==3){
        modificarPrecio();
    }
    else{
        printf("Respuesta no comprendida, vuelvalo a intentar");
    }
}

void borrar()
{
    FILE *arch;
    arch=fopen("productos.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de producto a eliminar: ");
    int cod;
    scanf("%i", &cod);
    tproducto producto;

    FILE *nuevo;
    nuevo=fopen("productos.tmp","ab");
    if (arch==NULL)
        exit(1);

    int existe=0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if (cod == producto.codigo)
        {
            printf("Eliminado %i %s $%0.2f\n", producto.codigo, producto.nombre, producto.precio);
            existe=1;
        }else{
            fwrite(&producto, sizeof(tproducto), 1, nuevo);
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0)
        printf("No existe un producto con dicho codigo\n");
    fclose(arch);
    fclose(nuevo);

    remove("productos.dat");
    rename("productos.tmp", "productos.dat");
    continuar();

}

int main()
{
    int opcion;
    do {
        printf("Este programa esta basado en el programa The office");
        printf("\n Bienvenido al sistema de almacenes de Dunder Mifflin Inc.");
        printf("\n 1. Ingresar un Nuevo producto al Almacen");
        printf("\n 2. Buscar algun papel en especifico");
        printf("\n 3. Lista del inventario completo");
        printf("\n 4. Modificar un articulo del inventario");
        printf("\n 5. Borrar un articulo del inventario");
        printf("\n 6. Formatear el inventario.");
        printf("\n 7. Salir");
        printf("\n\n Introduzca opcion (1-7): ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cargar();
                break;

            case 2:
                buscar();
                break;

            case 3:
                printf("\tCodigo  /  Nombre  /  Precio\n");
                lista();
                break;

            case 4:
                decisionModificacion();
                break;

            case 5:
                borrar();
                break;

            case 6:
                resetear();
                break;
        }

    } while (opcion != 7);

    return 0;
}
