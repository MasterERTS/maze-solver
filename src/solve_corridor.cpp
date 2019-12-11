#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
    typedef std::unique_ptr<Position> PositionPtr;

private:
    int m_distance;

public:
    // constructor from coordinates
    Position(int _x, int _y, int _distance = 1) : Point(_x, _y), m_distance(_distance) {}

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y){}

    int distToParent()
    {
        // in line-based motion, distance is the number of cell we could travel without hitting a wall
        return m_distance;
    }

    void print(const Point &parent) {
        int new_x;
        int new_y; 

        if (maze.isFree(x-1, y) && maze.isFree(x+1, y) && !maze.isFree(x, y + 1) && !maze.isFree(x, y - 1)) {
            //Corridor case one. Now that we're in a corridor check the children
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        new_x = x + 1;
                        new_y = y;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x + 1;
                            maze.passThrough(new_x, new_y);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                    case(1):
                        new_x = x - 1;
                        new_y = y;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x - 1;
                            maze.passThrough(new_x, new_y);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                }
            }
        } else if (!maze.isFree(x-1, y) && !maze.isFree(x+1, y) && maze.isFree(x, y + 1) && maze.isFree(x, y - 1)) {
            //Corridor case two ( top bottom )
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        new_x = x;
                        new_y = y + 1;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y + 1;
                            maze.passThrough(new_x, new_y);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                    case(1):
                        new_x = x;
                        new_y = y - 1;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y - 1;
                            maze.passThrough(new_x, new_y);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                }
            }
        }
    }

    void show(bool closed, const Point & parent) {
        const int b = closed?255:0, r = closed?0:255;

        int new_x;
        int new_y;
        maze.write(x, y, r, 0, b);

        if (maze.isFree(x-1, y) && maze.isFree(x+1, y) && !maze.isFree(x, y + 1) && !maze.isFree(x, y - 1)) {
            //Corridor case one. Now that we're in a corridor check the children
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        new_x = x + 1;
                        new_y = y;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x + 1;
                            maze.write(new_x, new_y, r, 0, b);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                    case(1):
                        new_x = x - 1;
                        new_y = y;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x - 1;
                            maze.write(new_x, new_y, r, 0, b);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                }
            }
        } else if (!maze.isFree(x-1, y) && !maze.isFree(x+1, y) && maze.isFree(x, y + 1) && maze.isFree(x, y - 1)) {
            //Corridor case two ( top bottom )
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        new_x = x;
                        new_y = y + 1;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y + 1;
                            maze.write(new_x, new_y, r, 0, b);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                    case(1):
                        new_x = x;
                        new_y = y - 1;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y - 1;
                            maze.write(new_x, new_y, r, 0, b);
                            if(new_x == parent.x && new_y == parent.y) return;
                        }
                        break;
                }
            }
        }

        // otherwise it should be an error
        return;
    }

    std::vector<PositionPtr> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<PositionPtr> generated;

        // Create new variables for Position, to prevent modifying the current node
        int new_x;
        int new_y;
        int distance;


        // Now you can have only two children max right ?
        if (maze.isFree(x-1, y) && maze.isFree(x+1, y) && !maze.isFree(x, y + 1) && !maze.isFree(x, y - 1)) {
            //Corridor case one. Now that we're in a corridor check the children
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        distance = 1;
                        new_x = x + distance;
                        new_y = y;
                        if(!maze.isFree(new_x, new_y)) break;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x + 1;
                            distance++;
                        }
                        generated.push_back(std::make_unique<Position>(x + 1, y, distance - 1));
                        break;
                    case(1):
                        distance = 1;
                        new_x = x - distance;
                        new_y = y;
                        if(!maze.isFree(new_x, new_y)) break;
                        while (maze.isFree(new_x, new_y)) {
                            new_x = new_x - 1;
                            distance++;
                        }
                        generated.push_back(std::make_unique<Position>(x - 1, y, distance - 1));
                        break;
                }
            }
        } else if (!maze.isFree(x-1, y) && !maze.isFree(x+1, y) && maze.isFree(x, y + 1) && maze.isFree(x, y - 1)) {
            //Corridor case two ( top bottom )
            for (int i = 0 ; i < 2 ; i++) {
                switch(i) {
                    case(0):
                        distance = 1;
                        new_x = x;
                        new_y = y + distance;
                        if(!maze.isFree(new_x, new_y)) break;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y + 1;
                            distance++;
                        }
                        generated.push_back(std::make_unique<Position>(x, y + 1, distance - 1));
                        break;
                    case(1):
                        distance = 1;
                        new_x = x;
                        new_y = y - distance;
                        if(!maze.isFree(new_x, new_y)) break;
                        while (maze.isFree(new_x, new_y)) {
                            new_y = new_y - 1;
                            distance++;
                        }
                        generated.push_back(std::make_unique<Position>(x, y - 1, distance - 1));
                        break;
                }
            }
        }
        return generated;
    }
};


int main( int argc, char **argv )
{
    // load file
    std::string filename = "maze.png";
    if(argc == 2)
        filename = std::string(argv[1]);

    // let Point know about this maze
    Position::maze.load(filename);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
             goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("corridor");
    cv::waitKey(0);

}
