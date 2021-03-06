#include <windows.h>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "bf.h"

#define PI 3.141593

using namespace std;

cell check_walkable(land bf[n][m], int px, int py, battle_robot* team, int rcount, int tm){
    if(bf[px][py] == WALL){
        return REST;
    } else for(int i = 0; i < rcount; i ++){
        if(team[i].pos.x == px && team[i].pos.y == py){
            if(team[i].tm == tm){
                return BOT_ALLY;
            }
            else{
                return BOT_ENEMY;
            }
        }
    }
    return FREE;
}

static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p)
            {xPos=xp; yPos=yp; level=d; priority=p;}

        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             level+=(dir==8?(i%2==0?10:14):10);
        }

        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;

            // Euclidian Distance
            d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);

            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return(d);
        }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish, land bf[n][m], battle_robot *bot)
{
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            if(check_walkable(bf, x, y, bot, TS, BLUE) == FREE){
                map[x][y] = 0;
            }else  map[x][y] = 1;
            closed_nodes_map[x][y] =0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish)
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx &&
                           pq[pqi].top().getyPos()==ydy))
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

void root_to_direction(string &route, direction *sequence){
    char c;
    int j;
    for(int i = 0; sequence[i] != NODIR; i++){
        sequence[i] =  NODIR;
    }
    direction dir;
    for(int i=0;i<route.length();i++){
        dir = NODIR;
        c =route.at(i);
        j=atoi(&c);
        if(dx[j] > 0){
            if(dy[j] > 0){
                dir = SE;
            } else if (dy[j] < 0){
                dir = NE;
            } else
                dir = E;
        } else if(dx[j] < 0){
            if(dy[j] > 0){
                dir = SW;
            } else if (dy[j] < 0){
                dir = NW;
            } else
                dir = W;
        } else {
            if(dy[j] > 0){
                dir = S;
            } else if (dy[j] < 0){
                dir = N;
            }
        }
        sequence[i] = dir;
    }
}

int walk_distance_count(direction dsourse, int sx, int sy, int dx, int dy, int count, direction *sequence){
    direction newDir = sequence[count];
    int newx, newy;
    switch(newDir){
    case N:
        newx = sx;
        newy = sy - 1;
        break;
    case NE:
        newx = sx + 1;
        newy = sy - 1;
        break;
    case E:
        newx = sx + 1;
        newy = sy;
        break;
    case SE:
        newx = sx + 1;
        newy = sy + 1;
        break;
    case S:
        newx = sx;
        newy = sy + 1;
        break;
    case SW:
        newx = sx - 1;
        newy = sy + 1;
        break;
    case W:
        newx = sx - 1;
        newy = sy;
        break;
    case NW:
        newx = sx - 1;
        newy = sy - 1;
        break;
    default:
        return 0;
    }
    int ddf = abs(newDir - dsourse);
    if(ddf != DC)
        ddf %= DC;
    if(newx == dx && newy == dy)
        return DC + ddf;
    int newc = count + 1;
    return ddf + DC + walk_distance_count(newDir, newx, newy, dx, dy, newc, sequence);
}

int bot_walk(battle_robot &bot, int count, direction *seq){

//Why didn't I think of it earlier? gonna implement as normal walk in further versions

    int diff = abs(bot.dir - seq[count]);
    if(diff != 4)
        diff %= 4;
    if(bot.currAp < 4+diff)
        return 1;
    bot.currAp -= (4+diff);
    bot.dir = seq[count];
    switch(bot.dir){
    case N:
        bot.pos.y -= 1;
        break;
    case NE:
        bot.pos.x += 1;
        bot.pos.y -= 1;
        break;
    case E:
        bot.pos.x += 1;
        break;
    case SE:
        bot.pos.x += 1;
        bot.pos.y += 1;
        break;
    case S:
        bot.pos.y += 1;
        break;
    case SW:
        bot.pos.x -= 1;
        bot.pos.y += 1;
        break;
    case W:
        bot.pos.x -= 1;
        break;
    case NW:
        bot.pos.y -= 1;
        bot.pos.x -= 1;
        break;
    default:
        return 1;
    }
    return 0;
}



int bot_turn(battle_robot &bot, int x, int y){
    direction dir = belongs_to_sector(bot, x, y);
    int diff = abs(dir - bot.dir);
    if(diff != 4)
        diff %= 4;
    if(dir != NODIR && diff <= bot.currAp){
        bot.dir = dir;
        bot.currAp -= diff;
        return 1;
    }
    return 0;
}

direction belongs_to_sector(battle_robot &bot, int x, int y){
    double angle = atan((double)(y - bot.pos.y)/(x - bot.pos.x));
    if(x >= bot.pos.x){
        if(angle >= PI/8.0 && angle < 3.0*PI/8.0)
            return SE;
        if(angle >= -PI/8.0 && angle <= PI/8.0)
            return E;
        if(angle >= -3.0*PI/8.0 && angle < -PI/8.0)
            return NE;
        if(angle >= -PI/2.0 && angle < -3.0*PI/8.0)
            return N;
        if(angle <= PI/2.0 && angle > 3.0*PI/8.0)
            return S;
    } else {
        if(angle >= PI/8.0 && angle < 3.0*PI/8.0)
            return NW;
        if(angle >= -PI/8.0 && angle <= PI/8.0)
            return W;
        if(angle >= -3.0*PI/8.0 && angle < -PI/8.0)
            return SW;
        if(angle >= -PI/2.0 && angle < -3.0*PI/8.0)
            return S;
        if(angle <= PI/2.0 && angle > 3.0*PI/8.0)
            return N;
    }
    return NODIR;
}
