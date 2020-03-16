#ifndef  _Stone_H_
#define  _Stone_H_

#include "cocos2d.h"
USING_NS_CC;


//棋子类
class Stone : public CCSprite
{
public:

    Stone();

    //棋子的类型:将、士、相、车、马、炮、兵
    enum TYPE {JIANG,SHI,XIANG,CHE,MA,PAO,BING};

    //创建棋子
    //第一个参数：棋子的类型
    //第二个参数：棋子的颜色
    static Stone* create(int id, bool red);
    
    //初始化棋子
     bool init(int id, bool red);

     //摆棋子
    void reset(bool red);

    //保存梅个棋子的初始位置
    static struct InitPos
    {
        int _x;
        int _y;
       Stone::TYPE _type;
    }_initPos[16];


     CC_SYNTHESIZE(TYPE, _type, Type)
    /*
    protected:
     Type _type;
public:
    void setType(Type var);
    {
        _type = type;
    }
    Type getType() const
    {
        return _type;
    }
*/

    CC_SYNTHESIZE(int, _x, X)
    CC_SYNTHESIZE(int, _y, Y)
    CC_SYNTHESIZE(int, _id, ID)
    CC_SYNTHESIZE(bool, _dead, Dead)
    CC_SYNTHESIZE(bool, _red, Red)
   /*//棋子的位置(坐标)
    int x;
    int y;

    int _id;//棋子的ID  0~31(一共有32个棋子)

    bool dead;//判断棋子是否被吃了

    bool _red;//判断棋子的颜色*/
};

#endif
