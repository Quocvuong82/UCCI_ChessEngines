/********************************************************************

	----------------------------------------------------------------
    软件许可证 － GPL
	版权所有 (C) 2005-2008 极速人工智能研究
	----------------------------------------------------------------
	这一程序是自由软件，你可以遵照自由软件基金会出版的GNU 通用公共许
	可证条款来修改和重新发布这一程序。或者用许可证的第二版，或者（根
	据你的选择）用任何更新的版本。

    发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定
	目地的隐含的担保。更详细的情况请参阅GNU通用公共许可证。

    你应该已经和程序一起收到一份GNU通用公共许可证的副本（本目录
	GPL.txt文件）。如果还没有，写信给：
    The Free Software Foundation, Inc.,  675  Mass Ave,  Cambridge,
    MA02139,  USA
	----------------------------------------------------------------
	如果你在使用本软件时有什么问题或建议，请用以下地址与我们取得联系：

			http://www.jsmaster.com

	或发信到：

			jschess##163.com
	----------------------------------------------------------------
	本文件用途：	略
	
	  
	本文件编写人：	
				顾剑辉			jschess##163.com
		
	本文件版本：	03
	最后修改于：	2006-1-16
		  
	注：以上E-Mail地址中的##请用@替换，这样做是为了抵制恶意的E-Mail
	地址收集软件。
	----------------------------------------------------------------
	修正历史：
			
		  2006-1		第一版发布

********************************************************************/
#include ".\move_check.h"
#include "move_do.h"
#include "attack.h"
#include "move_evasion.h"


static void find_pins(int list[]);
static void add_quiet_checks(list_t * list);

void gen_quiet_checks(list_t * list) 
{
	LIST_CLEAR(list);
	add_quiet_checks(list);
}
//抽子将军着法
static void add_quiet_checks(list_t * list)
{
	int me, opp;
	const sq_t * ptr;
	int from;
	int king;
	int inc;
	int pin[4];
	
	me = Turn;
    opp = COLOUR_OPP(me);

	find_pins(pin);

    king=Piece[opp<<4];

	for (ptr = pin; (from=*ptr) != SquareNone; ptr++) {
		if(from!=0)
		{
			inc=AttackTab[from-king + 256];
			 if((inc==16)||(inc==-16))
			     add_flee(list,from,true);
			 else
				 add_flee(list,from,false);
		}
	}

}
bool move_is_check(int move) {
	undo_t undo[1];
	int me;
    bool check=false;
	me=Turn;
	move_do(move,undo);
    check = is_in_check(me);
    move_undo(move,undo);
    return check;
}
//抽将
static void find_pins(int list[]) {

   int me, opp;
   int piece_tag;
   int pin;

   me = Turn;
   opp = COLOUR_OPP(me);
   
   piece_tag=me<<4;
   
   for(int i=1;i<15;++i)
   {
	   pin=Piece[piece_tag+i];
	   if(is_piece_pinned(pin,opp))
		   *list++ = pin;   
   }

  *list = SquareNone; 

}