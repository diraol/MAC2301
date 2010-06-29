#include <stdio.h>

class Noh {
   private:
   int valor;
   int peso; // número de descendentes + 1

   Noh* fe; // filho esquerdo
   Noh* fd; // filho direito

   public:
   Noh (int x) {
      valor = x;
      peso = 1;
      fe = fd = NULL;
   }

   void imprime () {
      printf("(%d ", valor);

      if (!fe) printf("^ ");
      else fe->imprime();

      if (!fd) printf("^ ");
      else fd->imprime();

      printf(") ");
   }

   void imprimePesos () {
      printf("(%d ", peso);

      if (!fe) printf("^ ");
      else fe->imprimePesos();

      if (!fd) printf("^ ");
      else fd->imprimePesos();

      printf(") ");
   }

   Noh* balanceia () {
      int e = 0, d = 0;

      if (fe) e = fe->peso;
      if (fd) d = fd->peso;

      if (d > 3*e + 1) {
         // mantendo a convenção do pdf
         int a = 0, n = 0;
         Noh* azul = this;
         Noh* verde = fd;
         Noh* roxo = fe;
         Noh* laranja = verde->fd; // verde != NULL pois d > 3e + 1

         if (roxo) n = roxo->peso;
         if (laranja) a = laranja->peso;

         if (a > n) {
            // mantendo a convenção do pdf
            int c = 0;
            Noh* vermelho = verde->fe; // verde != NULL pois d > 3e + 1

            if (vermelho) c = vermelho->peso;

            // acerta os ponteiros para uma árvore balanceada
            verde->fe = azul;
            azul->fd = vermelho;

            // recalcula os pesos
            azul->peso = n + c + 1;
            verde->peso = azul->peso + a + 1;

            return verde;
         }
         else {
            // mantendo a convenção do pdf
            int c = 0, b = 0;
            Noh* rosa = verde->fe; // verde != NULL pois d > 3e + 1
            Noh* vermelho = rosa->fe; // rosa != NULL pois !(a > n) implica 3n + e - a > 0
            Noh* cinza = rosa->fd; // mesmo motivo acima

            if (vermelho) c = vermelho->peso;
            if (cinza) b = cinza->peso;

            // acerta os ponteiros para uma árvore balanceada
            azul->fd = vermelho;
            verde->fe = cinza;
            rosa->fe = azul;
            rosa->fd = verde;

            // recalcula os pesos
            azul->peso = n + c + 1;
            verde->peso = b + a + 1;
            rosa->peso = azul->peso + verde->peso + 1;

            return rosa;
         }
      }
      else if (e > 3*d + 1) { // este bloco usa a convenção de nomes e cores espelhada.
         // mantendo a convenção do pdf
         int a = 0, n = 0;
         Noh* azul = this;
         Noh* verde = fe;
         Noh* roxo = fd;
         Noh* laranja = verde->fe; // verde != NULL pois d > 3e + 1

         if (roxo) n = roxo->peso;
         if (laranja) a = laranja->peso;

         if (a > n) {
            // mantendo a convenção do pdf
            int c = 0;
            Noh* vermelho = verde->fd; // verde != NULL pois d > 3e + 1

            if (vermelho) c = vermelho->peso;

            // acerta os ponteiros para uma árvore balanceada
            verde->fd = azul;
            azul->fe = vermelho;

            // recalcula os pesos
            azul->peso = n + c + 1;
            verde->peso = azul->peso + a + 1;

            return verde;
         }
         else {
            // mantendo a convenção do pdf
            int c = 0, b = 0;
            Noh* rosa = verde->fd; // verde != NULL pois d > 3e + 1
            Noh* vermelho = rosa->fd; // rosa != NULL pois !(a > n) implica 3n + e - a > 0
            Noh* cinza = rosa->fe; // mesmo motivo acima

            if (vermelho) c = vermelho->peso;
            if (cinza) b = cinza->peso;

            // acerta os ponteiros para uma árvore balanceada
            azul->fe = vermelho;
            verde->fd = cinza;
            rosa->fd = azul;
            rosa->fe = verde;

            // recalcula os pesos
            azul->peso = n + c + 1;
            verde->peso = b + a + 1;
            rosa->peso = azul->peso + verde->peso + 1;

            return rosa;
         }
      }
      else return this;
   }

   Noh* insere (int x) {
      if (x < valor) {
         if (!fe) fe = new Noh(x);
         else fe = fe->insere(x);
      }
      else {
         if (!fd) fd = new Noh(x);
         else fd = fd->insere(x);
      }
      peso++;
      return balanceia();
   }

   // remove o maior nó da árvore e põe seu valor em v
   Noh* removeMaior (int* v) {
      if (!fd) {
         *v = valor;
         return fe;
      }
      else {
         Noh* n = fd->removeMaior(v);
         peso--;

         if (fd != n) {
            delete fd;
            fd = n;
         }

         return balanceia();
      }
   }

   Noh* remove (int x) {
      if (x == valor) {
         if (!fe && !fd) return NULL;
         if (!fe) return fd;
         if (!fd) return fe;

         { // fd && fe
            Noh* n = fe->removeMaior(&valor);
            if (fe != n) {
               delete fe;
               fe = n;
            }
         }
      }
      else if (x < valor) {
         if (fe) {
            Noh* n = fe->remove(x);
            if (fe != n) {
               delete fe;
               fe = n;
            }
         }
      }
      else {
         if (fd) {
            Noh* n = fd->remove(x);
            if (fd != n) {
               delete fd;
               fd = n;
            }
         }
      }

      peso = 1;
      if (fe) peso += fe->peso;
      if (fd) peso += fd->peso;

      return balanceia();
   }

   bool pesosCorretos() {
      int pe, pd;
      if (fe) {
         if (!fe->pesosCorretos()) return false;
         pe = fe->peso;
      } else pe = 0;
      if (fd) {
         if (!fd->pesosCorretos()) return false;
         pd = fd->peso;
      } else pd = 0;
      return pe + pd + 1 == peso;
   }

   bool arvoreBalanceada() {
      int e = 0, d = 0;

      if (fe) {
         if (!fe->arvoreBalanceada()) return false;
         e = fe->peso;
      }

      if (fd) {
         if (!fd->arvoreBalanceada()) return false;
         d = fd->peso;
      }

      if (e > 3*d + 1 || d > 3*e + 1) return false;

      return true;
   }
};

class Arvore {
   private:
   Noh* n;

   public:
   Arvore () {
      n = NULL;
   }

   void imprime() {
      if (n) n->imprime();
      else printf("^");

      printf("\n");
   }

   void imprimePesos() {
      if (n) n->imprimePesos();
      else printf("^");

      printf("\n");
   }

   bool pesosCorretos() {
      if (n) return n->pesosCorretos();
      else return true;
   }

   bool arvoreBalanceada() {
      if (n) return n->arvoreBalanceada();
      else return true;
   }

   void insere (int x) {
      if (n) n = n->insere(x);
      else n = new Noh(x);
   }

   void remove (int x) {
      if (n) n = n->remove(x);
      if (n) n = n->balanceia();
   }
};

int main (void) {
   Arvore a;
   char c;
   int x;

   a.imprime();

   while (1) {
      c = getchar();

      if (c == '+') {
         scanf("%d", &x);
         printf("Inserindo %d\n",x);
         a.insere(x);
      }
      else if (c == '-') {
         scanf("%d", &x);
         printf("Removendo %d\n",x);
         a.remove(x);
      }
      else break;

      a.imprime();
      //a.imprimePesos();

      if (!a.pesosCorretos()) printf("Problema nos pesos\n");
      if (!a.arvoreBalanceada()) printf("Árvore desbalanceada\n");

      getchar();
   }

   return 0;
}
