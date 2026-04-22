// Bharath
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 512
#define MAX_CODE_LEN   256

// ── Node ─────────────────────────────────────────────────────────────────────

typedef struct HuffNode {
    int  ch;                    // character value; -1 for internal nodes
    long freq;
    struct HuffNode* left;
    struct HuffNode* right;
} HuffNode;

static HuffNode *huff_new_node(int ch, long freq) {
    HuffNode *n  = (HuffNode *)malloc(sizeof(HuffNode));
    n->ch        = ch;
    n->freq      = freq;
    n->left      = n->right = NULL;
    return n;
}

// ── Min-heap (priority queue) ─────────────────────────────────────────────────

typedef struct {
    HuffNode *nodes[MAX_TREE_NODES];
    int size;
} MinHeap;

static void heap_push(MinHeap *h, HuffNode *node) {
    int i = h->size++;
    h->nodes[i] = node;
    // bubble up
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->nodes[p]->freq > h->nodes[i]->freq) {
            HuffNode *tmp  = h->nodes[p];
            h->nodes[p]    = h->nodes[i];
            h->nodes[i]    = tmp;
            i = p;
        } else break;
    }
}

static HuffNode *heap_pop(MinHeap *h) {
    HuffNode *min  = h->nodes[0];
    h->nodes[0]    = h->nodes[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i+1, r = 2*i+2, s = i;
        if (l < h->size && h->nodes[l]->freq < h->nodes[s]->freq) s = l;
        if (r < h->size && h->nodes[r]->freq < h->nodes[s]->freq) s = r;
        if (s == i) break;
        HuffNode *tmp = h->nodes[i];
        h->nodes[i]   = h->nodes[s];
        h->nodes[s]   = tmp;
        i = s;
    }
    return min;
}

// ── Tree builder ──────────────────────────────────────────────────────────────

static HuffNode *build_huffman_tree(long freq[256]) {
    MinHeap heap;
    memset(&heap, 0, sizeof(MinHeap));
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            heap_push(&heap, huff_new_node(i, freq[i]));

    if (heap.size == 0) return NULL;

    while (heap.size > 1) {
        HuffNode *left  = heap_pop(&heap);
        HuffNode *right = heap_pop(&heap);
        HuffNode *par   = huff_new_node(-1, left->freq + right->freq);
        par->left  = left;
        par->right = right;
        heap_push(&heap, par);
    }
    return heap_pop(&heap);
}

// ── Code table generator ──────────────────────────────────────────────────────

static void generate_codes(HuffNode *root, char codes[256][MAX_CODE_LEN],
                            char *buf, int depth) {
    if (!root) return;
    if (root->ch != -1) {
        // Edge case: single unique character → assign code "0"
        buf[depth] = '\0';
        strcpy(codes[root->ch], depth == 0 ? "0" : buf);
        return;
    }
    buf[depth] = '0'; generate_codes(root->left,  codes, buf, depth + 1);
    buf[depth] = '1'; generate_codes(root->right, codes, buf, depth + 1);
}

// ── Cleanup ───────────────────────────────────────────────────────────────────

static void free_tree(HuffNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

#endif // HUFFMAN_H