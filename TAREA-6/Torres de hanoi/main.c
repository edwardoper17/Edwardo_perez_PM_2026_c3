#include <stdio.h>

void move(char origen, char destino) {
    printf("Mover disco de %c a %c\n", origen, destino);
}

void resolver(int n, char origen, char destino, char auxiliar) {
    if (n == 0) return;
    resolver(n - 1, origen, auxiliar, destino);
    move(origen, destino);
    resolver(n - 1, auxiliar, destino, origen);
}

int main() {
    int n = 5;
    resolver(n, 'A', 'C', 'B');
    return 0;
}
