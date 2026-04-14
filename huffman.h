// Bharath
struct Node{
    int freq;
    char letter;
    struct Node* left,right;
};

struct Node* createNode(unsigned long freq[256]){
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    
    for(int i=0; i<256;i++){
        if(freq[i]==0)
            continue;
        else{
            struct Node* new = (struct Node*)malloc(sizeof(struct Node));
        }
    }
}
