/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 * bbq :        Red-Black-Tree                                        *
 **********************************************************************/
/*
 * bbq:
 *  1. separate t when deleting it
 *
 * test:
 *  1. delete empty tree
 *  2. delete root
 *  3. insert a,b,c,...,z
*/

 /* library */
#include <stdio.h>
#include <cstdio>
#include <malloc.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <bitset>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

/* micros */
#define lowbit(x) ((x)&(-x))
#define leftson(x) ((x<<1)+1)
#define rightson(x) ((x<<1)+2)
#define parent(x) ((x-1)>>1)
#define mid(x,y) (((x)+(y))>>1)

/* functions */
template<class T>
inline int ABS(T a) { return a < 0 ? -a : a; }
template<class T>
inline void MYSWAP(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}
void init();

/* pragmas */
#pragma warning(disable:4996)

/* const variables */
const int INF_INT = 1 << 29;
const double PI = acos((double)-1);
const double INF = 1e20;
const double EPS = 1e-6;
//freopen("test.txt", "w", stdout);

/* code start here */
#define RB RedBlueTreeNode
#define RBT RedBlackTree
#define lc leftchild
#define rc rightchild
#define f father
#define RED 0
#define BLACK 1
#define TIP 9
#define LeftSlash '/'
#define RightSlash '\\'
#define BLANK ' '
#define MAXCACHE 300

enum operation {
    ERROR = 0,
    INSERT = 1,
    DELETEWITHVALUE = 2,
    DELETERBT = 3,
    EXIT = 4
};

struct RB {
    RB *father, *leftchild, *rightchild;
    bool color;/* default color is red(insert) */
    int row, col, depth; /* for print */
    char value;
    RB() :f(NULL), lc(NULL), rc(NULL), color(RED) {}
    RB(char _value) :f(NULL), lc(NULL), rc(NULL), color(RED), value(_value) {}
    RB(RB *_f, RB *_lc, RB * _rc, char _value)
        :f(_f), lc(_lc), rc(_rc), color(RED), value(_value) {}
};

struct RBT {
    RB *Root;
    int totalNode;
    int height;
    RBT() :Root(NULL), totalNode(0), height(0) {}
};

/* Global variables */
static const char* tip[] = {
    "    this a visualization for Red-Black-Tree",
    "    the input element must be a CAHR between 'a' and 'z', ['a','z']",
    "    the volume of the RBT is at most 26",
    "    command:",
    "        1,a :    insert 'a'",
    "        2,c :    delete element with value 'c'",
    "        3,a :    delete the Red-Black-Tree, 'a' can be arbitrary letter",
    "        4,a :    exit, 'a' can be arbitrary letter",
    "    ATTENTION: UPPERCASE letters mean BLACK, LOWERCASE letters mean RED"
};
static RBT *tree;
static int mostRightFlag[MAXCACHE];
static char T[MAXCACHE][MAXCACHE];
static int deepest;
static const int BIG = 'A' - 'a';

/* functions */
void helpinfo();/* show some tips */
operation getCommand(char *val);
bool insert(char val);
bool find(char val, RB **t);
bool del(char val);
void printRBT();
void changeColorForInsert(RB *t);
void deleteEleWithNoChildren(RB *t);
void deleteEleWithOneChild(RB *t);
void changeForDoubleBlack(RB *t);
void delRBT();
void dfsDelRB(RB *t);
void makeArray(RB *root);
void calHeight(RB *root);

int main() {
    /* parameters */
    bool flush;/* should the cmd be flushed? */
    char val;/* for insert/delete */
    /* initial */
    init();
    helpinfo();
    bool exitFlag = false;/* exit flag */
    /* loop for visualization */
    while (1) {
        flush = true;
        /* get command */
        switch (getCommand(&val)) {
        case ERROR:
            printf("bad input\n");
            flush = false;
            break;
        case INSERT:
            if (tree->totalNode == 100) {
                printf("Overloaded! Insertion failed!");
                break;
            }
            if (!insert(val)) {
                flush = false;
                printf("\'%c\' is already in the RBT\n", val);
            }
            break;
        case DELETEWITHVALUE:
            if (!del(val)) {
                flush = false;
                printf("\'%c\' is not in the RBT\n", val);
            }
            break;
        case EXIT:
            exitFlag = true;
        case DELETERBT:
            delRBT();
            break;
        default:
            break;
        }
        /* input conflict */
        if (!flush) continue;
        /* output */
        system("cls");/* flush the cmd */
        helpinfo();
        printRBT();
        if (exitFlag) break;
    }
    system("pause");
    return 0;
}

/* calculate the depth of every RB-node */
void calHeight(RB *root) {
    int depth = root->depth + 1;
    if (depth > deepest) deepest = depth;
    if (root->leftchild) {
        root->leftchild->depth = depth;
        calHeight(root->leftchild);
    }
    if (root->rightchild) {
        root->rightchild->depth = depth;
        calHeight(root->rightchild);
    }
}

/* calculate the row/col of every node*/
void makeArray(RB *root) {
    /* BLACK -> UPPER LETTERS */
    if (root->color == RED)
        T[root->row][root->col] = root->value;
    else
        T[root->row][root->col] = (root->value) + BIG;
    if (mostRightFlag[root->row] < root->col + 1) {
        mostRightFlag[root->row] = root->col + 1;
    }
    if (root->leftchild) {
        T[root->row + 1][root->col - 1] = LeftSlash;
        mostRightFlag[root->row + 1] = root->col;
        root->leftchild->row = root->row + 2;
        root->leftchild->col = root->col - (1 << (deepest - 1 - root->depth));
        makeArray(root->leftchild);
    }
    if (root->rightchild) {
        T[root->row + 1][root->col + 1] = RightSlash;
        mostRightFlag[root->row + 1] = root->col + 2;
        root->rightchild->row = root->row + 2;
        root->rightchild->col = root->col + (1 << (deepest - 1 - root->depth));
        makeArray(root->rightchild);
    }
}


void printRBT() {
    if (tree->Root == NULL) {
        printf("Red-Black-Tree is empty\n");
        return;
    }
    /* initial */
    memset(T, 0, sizeof(T));
    deepest = 0;
    memset(mostRightFlag, 0, sizeof(mostRightFlag));
    /* deal with height */
    tree->Root->depth = 0;
    calHeight(tree->Root);
    tree->height = deepest;
    /* deal with T */
    tree->Root->col = 110;
    tree->Root->row = 0;
    makeArray(tree->Root);
    /* output */
    printf("height:%d, number:%d\n", tree->height, tree->totalNode);
    int depth = (deepest << 1) - 1;
    int minLeft = 110 - (1 << deepest);
    for (int i = 0; i < depth; ++i) {
        for (int j = minLeft + 1;; ++j) {
            if (j == mostRightFlag[i]) {
                printf("\n");
                break;
            }
            if (T[i][j]) printf("%c", T[i][j]);
            else printf(" ");
        }
    }
}

/* delete the tree on recursion */
void dfsDelRB(RB *t) {
    if (!t) return;
    if (t->leftchild) dfsDelRB(t->leftchild);
    if (t->rightchild) dfsDelRB(t->rightchild);
    delete t;
}

/* delete RBT */
void delRBT() {
    dfsDelRB(tree->Root);
    tree->Root = NULL;
    tree->totalNode = 0;
}

/* t!=root */
void changeForDoubleBlack(RB *t) {
    RB *father = t->father;
    RB *brother, *uncle, *grandpa = father->father;
    bool left1 = false;
    bool left2 = (father->leftchild == t);
    /* brother */
    if (left2) brother = father->rightchild;
    else brother = father->leftchild;
    if (grandpa) {
        left1 = (grandpa->leftchild == father);
        if (left1) uncle = grandpa->rightchild;
        else uncle = grandpa->leftchild;
    }
    /*
     * case 1: brother->color = RED,
     * rotate, so that brother->color = BLACK
     *
     *      (* BLACK)
     * case 1.1
     *        father*                     brother*
     *        /     \                     /     \
     *      *t*    brother      ->     father    br*
     *              /  \               /    \
     *             bl*   br*          *t*   bl*
     *
     *  colorchanged: brother, father
     *
     * case 1.2
     *        father*                     brother*
     *        /     \                     /     \
     *     brother  *t*       ->        bl*    father
     *      /  \                                /    \
     *    bl*   br*                            br*   *t*
     *
     *  colorchanged: brother, father
    */
    if (brother->color == RED) {
        /* color */
        brother->color = BLACK;
        father->color = RED;
        /* position */
        /* 0 */
        if (grandpa) {
            if (left1) grandpa->leftchild = brother;
            else grandpa->rightchild = brother;
        }
        else tree->Root = brother;
        brother->father = grandpa;
        /* left */
        if (left2) {
            /* 1 */
            father->rightchild = brother->leftchild;
            if (brother->leftchild) brother->leftchild->father = father;
            /* 2 */
            brother->leftchild = father;
            father->father = brother;
        }
        /* right */
        else {
            /* 1 */
            father->leftchild = brother->rightchild;
            if (brother->rightchild) brother->rightchild->father = father;
            /* 2 */
            brother->rightchild = father;
            father->father = brother;
        }
    }
    /* fall through, case 1 -> case 2,3 */
    /*
     * case 2: BLACK brother has two BLACK children
     * brother->color = t->color = RED, grandpa->color = BLACK
     */
    else if (((brother->leftchild == NULL) || (brother->leftchild->color == BLACK))
        && ((brother->rightchild == NULL) || (brother->rightchild->color == BLACK))) {
        brother->color = RED;
        if (father->color == RED || father == tree->Root) {
            father->color = BLACK;
            /* delete t */
            if (left2) father->leftchild = NULL;
            else father->rightchild = NULL;
            return;
        }
        /* else */
        father->color = BLACK;
        changeForDoubleBlack(father);
    }
    /* case 3: BLACK brother has at least one RED child */
    else {
        bool fatherColor = father->color;
        RB *bl = brother->leftchild;
        RB *br = brother->rightchild;
        if (br && br->color == RED) {
            if (left1) {
                /* case 3.1
                 *
                 *      (*, BLACK)
                 *      (?, not sure)
                 *      (!, special color)
                 *
                 *      father!                          brother!
                 *      /     \                          /     \
                 *    *t*   brother*        ->        father*   br*
                 *           /   \                    /   \
                 *          bl?   br                 t*   bl?
                 */
                /* color */
                brother->color = fatherColor;
                father->color = BLACK;
                br->color = BLACK;
                /* position */
                /* 0 */
                if (grandpa) {
                    if (left1) grandpa->leftchild = brother;
                    else grandpa->rightchild = brother;
                }
                else tree->Root = brother;
                brother->father = grandpa;
                /* 1 */
                father->rightchild = bl;
                if (bl) bl->father = father;
                /* 2 */
                father->father = brother;
                brother->leftchild = father;
                /* 3 */
                father->leftchild = NULL;/* delete t */
            }
            else {
                /* case 3.2:
                *
                *      (*, BLACK)
                *      (?, not sure)
                *      (!, special color)
                *
                *          father!                         br!
                *         /      \                       /    \
                *      brother*  *t*        ->      brother* father*
                *       /    \                        /  \     /   \
                *      bl?   br                     bl? brl?  brr?  t*
                *           /  \
                *         brl? brr?
                */
                RB *brl = br->leftchild, *brr = br->rightchild;
                /* color */
                br->color = fatherColor;
                father->color = BLACK;
                /* position */
                /* 0 */
                if (grandpa) {
                    if (left1) grandpa->leftchild = br;
                    else grandpa->rightchild = br;
                }
                else tree->Root = br;
                br->father = grandpa;
                /* 1 */
                br->leftchild = brother;
                brother->father = br;
                br->rightchild = father;
                father->father = br;
                /* 2 */
                brother->rightchild = brl;
                if (brl) brl->father = brother;
                father->leftchild = brr;
                if (brr) brr->father = father;
                /* 3 */
                father->rightchild = NULL;/* delete t */
            }
        }
        else {
            if (left1) {
                /* case 3.3
                 *
                 *      (*, BLACK)
                 *      (?, not sure)
                 *      (!, special color)
                 *
                 *      father!                              bl!
                 *      /     \                          /        \
                 *    *t*   brother*        ->        father*   brother*
                 *           /   \                    /   \      /   \
                 *          bl   br?                 t*   bll?  blr?  br?
                 *         /  \
                 *       bll?  blr?
                 *
                */
                RB *bll = bl->leftchild, *blr = bl->rightchild;
                /* color */
                bl->color = fatherColor;
                father->color = BLACK;
                /* position */
                /* 0 */
                if (grandpa) {
                    if (left1) grandpa->leftchild = bl;
                    else grandpa->rightchild = bl;
                }
                else tree->Root = bl;
                bl->father = grandpa;
                /* 1 */
                bl->leftchild = father;
                father->father = bl;
                bl->rightchild = brother;
                brother->father = bl;
                /* 2 */
                father->rightchild = bll;
                if (bll) bll->father = father;
                brother->leftchild = blr;
                if (blr) blr->father = brother;
                /* 3 */
                father->leftchild = NULL;/* delete t */
            }
            else {
                /* case 3.4:
                *
                *      (*, BLACK)
                *      (?, not sure)
                *      (!, special color)
                *
                *          father!                       brother!
                *         /      \                       /    \
                *      brother*  *t*        ->         bl*   father*
                *       /    \                                /   \
                *      bl   br?                              br?  t*
                *
                */
                /* color */
                father->color = BLACK;
                brother->color = fatherColor;
                bl->color = BLACK;
                /* position */
                /* 0 */
                if (grandpa) {
                    if (left1) grandpa->leftchild = brother;
                    else grandpa->rightchild = brother;
                }
                else tree->Root = brother;
                brother->father = grandpa;
                /* 1 */
                father->leftchild = br;
                if (br) br->father = father;
                /* 2 */
                father->father = brother;
                brother->rightchild = father;
                /* 3 */
                father->rightchild = NULL;/* delete t */
            }
        }
    }
}

/*
 * should delete t
 * t != root
*/
void deleteEleWithNoChildren(RB *t) {
    RB *father = t->father;
    bool left1 = false, left2 = false;
    left2 = (father->leftchild == t);
    /* deal */
    /* t->color = RED, delete t and return */
    if (t->color == RED) {
        if (left2) father->leftchild = NULL;
        else father->rightchild = NULL;
    }
    /* t->color = BLACK, !!double black!! */
    else changeForDoubleBlack(t);
    /* delete */
    delete t;
}

/*
 * delete the element(t) who has one child,
 * t->color = BLACK
 * t->son->color = RED
*/
void deleteEleWithOneChild(RB *t) {
    RB *father = t->father;
    /* left or right */
    RB *son = (t->leftchild) ? (t->leftchild) : (t->rightchild);
    /* t != root */
    if (t != tree->Root) {
        if (father->leftchild == t) father->leftchild = son;
        else father->rightchild = son;
    }
    else tree->Root = son;
    son->father = father;
    son->color = BLACK;
    delete t;
}

/* false: can't find the element */
bool del(char val) {
    RB *t;
    if (!find(val, &t)) return false;
    /* delete the ele, change color */
    /* delete */
    /* last */
    if (tree->totalNode == 1) {
        tree->totalNode = 0;
        delete tree->Root;
        tree->Root = NULL;
        return true;
    }
    /* normal */
    --(tree->totalNode);
    /* case 1: t has no children */
    if (!(t->leftchild) && !(t->rightchild)) deleteEleWithNoChildren(t);
    /* case 2: t has two children */
    else if ((t->leftchild) && (t->rightchild)) {
        RB *f;
        /* all values are char(int) */
        find((t->value) + 1, &f);/* trick */
        MYSWAP(f->value, t->value);
        if (f->leftchild || f->rightchild) deleteEleWithOneChild(f);
        else deleteEleWithNoChildren(f);
    }
    /* case 3: t has one child */
    else deleteEleWithOneChild(t);
    return true;
}

/*
 * true:  find the val, *t = val(for delete)
 * false: do not find the val , t = father(for insert)
*/
bool find(char val, RB **t) {
    if (tree->Root == NULL) {
        t = NULL;
        return false;
    }
    RB *tmp = tree->Root;
    while (tmp->value != val) {
        if (tmp->value < val) {
            if (!tmp->rightchild) {
                *t = tmp;
                return false;
            }
            else tmp = tmp->rightchild;
        }
        else {
            if (!tmp->leftchild) {
                *t = tmp;
                return false;
            }
            else tmp = tmp->leftchild;
        }
    }
    *t = tmp;
    return true;
}

/* f->color is RED */
void changeColorForInsert(RB * t) {
    /* case 0: t = root, t->color = BLACK */
    if (t == tree->Root) {
        t->color = BLACK;
        return;
    }
    /* case 1: t->father->color = BLACK */
    if (t->father->color == BLACK) return;
    /* para start, t has father/grandpa */
    RB *father = t->father;
    RB *grandpa = father->father;
    RB *uncle, *brother;
    bool left1 = false, left2 = false;/* compress */
    /* uncle */
    if (grandpa->leftchild == father) {
        left1 = true;
        uncle = grandpa->rightchild;
    }
    else uncle = grandpa->leftchild;
    /* brother */
    if (father->leftchild == t) {
        brother = father->rightchild;
        left2 = true;
    }
    else brother = father->leftchild;
    /* para end */
    /* case 2: t->uncle->color = RED, transfer */
    if (uncle && uncle->color == RED) {
        father->color = BLACK;
        uncle->color = BLACK;
        grandpa->color = RED;
        changeColorForInsert(grandpa);
        return;
    }
    /* case 3: t->uncle->color = BLACK, rotate*/
    /* grandpa = root => grandpa->father = NULL*/
    RB *gg = grandpa->father;
    bool left3 = true;
    if (gg) left3 = (gg->leftchild == grandpa);
    /* rightRotate */
    /*     (* -> RED)
     *
     *      grandpa                     father
     *     /       \                   /      \
     *  father*    uncle        ->    t*     grandpa*
     *   / \                                  /   \
     *  t*  brother                      brother  uncle
    */
    if (left1 && left2) {
        /* color */
        father->color = BLACK;
        grandpa->color = RED;
        /* position */
        /* 1 */
        if (gg) {
            if (left3) gg->leftchild = father;
            else gg->rightchild = father;
        }
        else tree->Root = father;
        father->father = gg;
        /* 2 */
        grandpa->leftchild = brother;
        brother->father = grandpa;
        /* 3 */
        grandpa->father = father;
        father->rightchild = grandpa;
    }
    /* leftRotate */
    /*     (* -> RED)
     *
     *      grandpa                        father
     *     /       \                      /      \
     *  uncle    father*      ->      grandpa*    t*
     *            /   \                /   \
     *        brother  t*           uncle  brother
    */
    else if (!left1 && !left2) {
        /* color */
        father->color = BLACK;
        grandpa->color = RED;
        /* position */
        /* 1 */
        if (gg) {
            if (left3) gg->leftchild = father;
            else gg->rightchild = father;
        }
        else tree->Root = father;
        father->father = gg;
        /* 2 */
        grandpa->rightchild = brother;
        if (brother) brother->father = grandpa;
        /* 3 */
        grandpa->father = father;
        father->leftchild = grandpa;
    }
    /* rightUp */
    /*     (* -> RED)
     *
     *      grandpa                          t
     *     /       \                      /      \
     *  uncle    father*      ->      grandpa*  father*
     *            /   \                /   \     /   \
     *           t*  brother        uncle  t-l  t-r  brother
     *
     *                                  t-l = t-r = NULL
    */
    else if (!left1 && left2) {
        /* color */
        t->color = BLACK;
        grandpa->color = RED;
        /* position */
        /* 1 */
        if (gg) {
            if (left3) gg->leftchild = t;
            else gg->rightchild = t;
        }
        else tree->Root = t;
        t->father = gg;
        /* 2 */
        grandpa->rightchild = NULL;
        father->father = t;
        father->leftchild = NULL;
        /* 3 */
        t->leftchild = grandpa;
        t->rightchild = father;
    }
    /* leftUp */
    /*     (* -> RED)
     *
     *        grandpa                          t
     *       /       \                      /      \
     *   father*    uncle      ->      father*   grandpa*
     *   /     \                       /    \     /   \
     * brother  t*                  brother t-l  t-r  uncle
     *
     *                                  t-l = t-r = NULL
    */
    else {
        /* color */
        t->color = BLACK;
        grandpa->color = RED;
        /* position */
        /* 1 */
        if (gg) {
            if (left3) gg->leftchild = t;
            else gg->rightchild = t;
        }
        else tree->Root = t;
        t->father = gg;
        /* 2 */
        grandpa->leftchild = NULL;
        father->father = t;
        father->rightchild = NULL;
        /* 3 */
        t->leftchild = father;
        t->rightchild = grandpa;
    }
}

/* false means the value is already in the tree */
bool insert(char val) {
    /* first */
    if (tree->Root == NULL) {
        tree->Root = new RB();
        tree->Root->color = BLACK;
        tree->Root->value = val;
        ++(tree->totalNode);
        return true;
    }
    /* normal */
    RB *f;
    if (find(val, &f)) return false;
    /* insert */
    ++(tree->totalNode);
    /* right */
    if (f->value < val) {
        f->rightchild = new RB(f, NULL, NULL, val);
        f->rightchild->father = f;
        f = f->rightchild;
    }
    /* left */
    else {
        f->leftchild = new RB(f, NULL, NULL, val);
        f->leftchild->father = f;
        f = f->leftchild;
    }
    /* change color, important! */
    changeColorForInsert(f);
    return true;
}

/* get the command */
operation getCommand(char *value) {
    int cmd;
    char val[10];
    scanf("%d %s", &cmd, val);
    /* bad input */
    if (val[1]) return ERROR;
    /* change to small */
    if (val[0] >= 'A' && val[0] <= 'Z') val[0] -= BIG;
    *value = val[0];
    operation op;
    switch (cmd) {
    case 1:
        if (val[0] >= 'a' && val[0] <= 'z') op = INSERT;
        else op = ERROR;
        break;
    case 2:
        op = DELETEWITHVALUE;
        break;
    case 3:
        op = DELETERBT;
        break;
    case 4:
        op = EXIT;
        break;
    default:
        op = ERROR;
        break;
    }
    return op;
}

/* show some tips */
void helpinfo() {
    /* head */
    printf("+"); for (int i = 2; i < 80; ++i) printf("-"); printf("+\n");
    /* body */
    for (int i = 0; i < TIP; ++i) printf("|%-78s|\n", tip[i]);
    /* tail */
    printf("+"); for (int i = 2; i < 80; ++i) printf("-"); printf("+\n");
}

/* initial */
void init() {
    tree = new RBT();
}
