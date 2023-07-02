#define print printf

int main(){
    int i;
    int j;
    int k;
    i = 0;
    j = 1;
    k = 1;
    while(i < 10){
        j = add(j, k);
        print("%d", j);
        k = add(j, k);
        print("%d", k);
        i = i + 1;
    }
}

int add(int a, int b){
    return a + b;
}