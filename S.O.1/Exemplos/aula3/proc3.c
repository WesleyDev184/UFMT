#include <unistd.h>

int main(){
    for(int i = 0; i <3;i++){
        fork();
        return 0;
}