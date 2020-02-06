# Red-Black-Tree 红黑树
## 1. 红黑树的定义
1. 是一棵扩充二叉树, **所有的空指针也看做是结点**
2. 是一棵BST树
3. 每一个节点都有颜色, 红色(R)或者黑色(B)
4. 根结点是黑色(B), 所有的空指针都是黑色(B)
5. 不允许有连续的两个红色(R)结点
6. 结点到其子孙外部结点的简单路径上的黑色节点数目相同

## 2. 红黑树的相关性质和说明
1. 结点的阶(rank)指从这个结点到其任意子孙外部结点上的黑色节点数目(**不包括自身, 包括叶节点**)
2. 红黑树的阶(rank)指根(root)的阶(rank)

## 3. 红黑树插入算法
```C
0. 插入结点为红色, 记作 t
1. 按照BST树的插入算法插入结点
2. case 1: 插入结点的父节点为黑色(B), 结束
   case 2: 插入结点的父节点为红色(R), 红红冲突(有两个相邻结点为红色(R)), 进行调整
3. 红红冲突调整算法
   case 1: 插入结点的叔父结点为黑色(B), 旋转调整
           (带'*'标记的为红色)
           (实际上,  t-l = t-r = NULL)                                       
             
     case 1.1: LL -> 右旋    
     
                grandpa                     father
               /       \                   /      \
            father*    uncle      ->      t*     grandpa*
             / \                                  /   \
            t*  brother                      brother  uncle
  
     case 1.2: RR -> 左旋
     
                grandpa                        father
               /       \                      /      \
            uncle    father*      ->      grandpa*    t*
                      /   \                /   \
                  brother  t*           uncle  brother
        
     case 1.3: LR -> 提升
  
               grandpa                            t
              /       \                        /      \
          father*    uncle        ->      father*   grandpa*
          /     \                         /    \     /   \
        brother  t*                    brother t-l  t-r  uncle

     case 1.4: RL -> 提升
  
              grandpa                            t
             /       \                        /      \
          uncle    father*        ->      grandpa*  father*
                    /   \                  /   \     /   \
                   t*  brother          uncle  t-l  t-r  brother
                   
   case 2: 插入结点的叔父结点为红色(R), 换色调整
           父结点、叔父结点变为黑色(B), 祖父节点变为红色(R)
      case 2.1 祖父节点是根节点, 祖父节点变为黑色(B), 调整结束
      case 2.2 祖父结点的父节点为黑色(B), 调整结束
      case 2.3 祖父结点的父节点为红色(R), 对祖父节点进行红红冲突调整算法
```

## 4. 红黑树删除算法
```C
0. 带'*'标记的为黑色(B)
   带'?'标记的为原来该结点的颜色
   带'!'标记的为原来该位置的颜色
1. 删除操作(待删除的结点记作t)
   case 1: 待删除结点只有一个非空子节点
           推断出该结点为黑色(B), 非空子结点为红色(R), 结构如下
           
                       |                      |
                       t*                     t*     
                    /     \        or      /      \              
                  NULL*   son            son     NULL*
         
           调整后结构如下:
           
                    |
                   son*
                   
   case 2: 待删除结点没有非空子结点, 两个子节点都是 NULL
     case 2.1: 待删除结点为红色(R), 直接删除即可
     
                       |                      |
                       t           ->       NULL*
                    /     \     
                  NULL*  NULL*
                  
     case 2.2: 待删除结点为黑色(B), 对下述标记节点(**)进行双黑调整算法
               (双黑指的是这个结点代表了两个黑节点(BB))
               
                       |                      |
                       t           ->       *NULL*
                    /     \     
                  NULL*  NULL*
                      
   case 3: 待删除结点有两个非空子结点, 找到该结点在BST树中的后继 m, 
           t与m换值不换色, 此时m至少有一个非空子结点, 对m进行删除操作 
   
2. 双黑调整算法(待调整结点记作t)
   case 1: 待删除结点的兄弟结点为黑色(B), 进行调整将其兄弟结点转化为黑色(B), 再对其调用双黑调整算法
     case 1.1: t是左儿子
     
            father*                     brother*
            /     \                     /     \
          *t*    brother      ->     father    br*
                  /  \               /    \
                 bl*   br*          *t*   bl*
    
     case 1.2: t是右儿子
     
              father*                     brother*
              /     \                     /     \
           brother  *t*       ->        bl*    father
            /  \                                /    \
          bl*   br*                            br*   *t*
          
   case 2: 待删除结点的兄弟结点为红色(R)
     case 2.1: 待删除结点的兄弟结点(R)的两个儿子都是黑色(B), 进行换色调整
               如果待删除结点的父结点原来是红色(R), 进行以下调整后结束
               如果待删除结点的父结点原来是黑色(B), 进行如下调整后还要对父结点调用双黑调整算法
               
       case 2.1.1: t是左儿子

               father?                    father*        
              /      \                    /     \        
            *t*   brother*      ->     t*     brother   
                    /  \                       /  \     
                   bl*   br*                  bl*   br* 

       case 2.1.2: t是右儿子

                father?                       father*    
                /      \                      /     \    
             brother*  *t*       ->       brother    t*  
              /  \                         /  \         
            bl*   br*                    bl*   br*    
      case 2.2: 待删除结点的兄弟结点(R)至少有一个红色子节点(R), 进行旋转调整
                (如果有两个任选一个就行)
        case 2.2.1: L-RR
        
               father!                           brother!
               /     \                           /     \
             *t*   brother*      ->        father*     br*
                    /   \                     /   \
                   bl?   br                  t*   bl?
          
        case 2.2.2:  R-LR   
        
                father!                         br!
               /      \                       /    \
            brother*  *t*        ->      brother* father*
             /    \                        /  \     /   \
            bl?   br                     bl? brl?  brr?  t*
                 /  \
               brl? brr?        
               
        case 2.2.3:  L-RL      
        
             father!                              bl!
             /     \                          /        \
           *t*   brother*        ->        father*   brother*
                  /   \                    /   \      /   \
                 bl   br?                 t*   bll?  blr?  br?
                /  \
              bll?  blr?        
              
        case 2.2.4:  R-LL          
        
                father!                       brother!
               /      \                       /    \
            brother*  *t*        ->         bl*   father*
             /    \                                /   \
            bl   br?                              br?  t*
        
```
## 5.参考资料
1. 张铭,赵海燕,王腾蛟. 数据结构与算法. 北京: 高等教学与出版社, 2008.6, [P322-328](./RBT.pdf)
