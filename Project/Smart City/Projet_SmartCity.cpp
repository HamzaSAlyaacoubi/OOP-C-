using namespace std;
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>

Color sideColor = {0, 0, 0, 100};

class TrafficLight
{
private:
    int x, y;
    int state; // 0 = red, 1 = yellow, 2 = green
    float timer;

public:
    TrafficLight(int px, int py)
    {
        x = px;
        y = py;
        state = 1; // start at red
        timer = 0.0f;
    }

    friend class Vehicle;

    void Update(float dt)
    {
        timer += dt;

        if (timer >= 2.0f)
        { // change every 2 seconds
            state = (state + 1) % 3;
            timer = 0.0f;
        }
    }

    void Draw() const
    {
        DrawRectangle(x, y, 40, 100, DARKGRAY);

        // Lights (only one bright at a time)

        DrawCircle(x + 20, y + 20, 12.5, state == 0 ? RED : Fade(RED, 0.3f));       // Red
        DrawCircle(x + 20, y + 50, 12.5, state == 2 ? YELLOW : Fade(YELLOW, 0.3f)); // Yellow
        DrawCircle(x + 20, y + 80, 12.5, state == 1 ? GREEN : Fade(GREEN, 0.3f));   // Green
    }

    int getState() { return state; }

    ~TrafficLight() {}
};

struct RoadNode
{
    Vector2 position;
    vector<int> next; // indices of next nodes
};

struct RoadGraph
{
    vector<RoadNode> nodes;

    int AddNode(Vector2 pos)
    {
        nodes.push_back({pos});
        return nodes.size() - 1;
    }

    void Connect(int from, int to)
    {
        nodes[from].next.push_back(to);
    }

    void ClearNodes()
    {
        nodes.clear();
    }
};

vector<Vector2> GeneratePath(RoadGraph &graph, int startNode)
{
    vector<Vector2> path;
    int current = startNode;

    path.push_back(graph.nodes[current].position);

    while (!graph.nodes[current].next.empty())
    {
        auto &choices = graph.nodes[current].next;
        int nextIndex = choices[GetRandomValue(0, choices.size() - 1)];
        current = nextIndex;
        path.push_back(graph.nodes[current].position);
    }

    return path;
}

enum TurnType
{
    TL,
    BL,
    TR,
    BR
};
class Road
{

protected:
    float width;
    float height;

public:
    Road(float w, float h = 0)
    {
        width = w;
        height = h;
    }

    virtual ~Road() {}
};

class VerticalRoad : public Road
{
private:
    int counter = 0;
    int nbrRoads;

public:
    VerticalRoad(float width, float height, int nbr) : Road(width, height) { nbrRoads = nbr; }

    void Draw(float xPos, float yPos)
    {
        float lineWidth = width / 50;
        float lineHeight = height / 2;
        Rectangle vertRoad = {xPos, yPos, width, height};
        DrawRectangleRec(vertRoad, DARKGRAY);
        Rectangle vertRoadLine = {xPos + (width / 2) - (lineWidth / 2), yPos + (height / 4), lineWidth, lineHeight};
        DrawRectangleRec(vertRoadLine, WHITE);
    }

    float getHeight() { return height; } // to do ovveride after //
    float getWidth() { return width; }
    int getNbrRoads() { return nbrRoads; }
};
class HorizontalRoad : public Road
{
private:
    int nbrRoads;

public:
    HorizontalRoad(float width, float height, int nbr) : Road(width, height) { nbrRoads = nbr; }

    void Draw(float xPos, float yPos)
    {
        float lineWidth = width / 2;
        float lineHeight = height / 100;
        Rectangle horRoad = {xPos, yPos, width, height};
        DrawRectangleRec(horRoad, DARKGRAY);
        Rectangle horRoadLine = {xPos + (width / 4), yPos + (height / 2) - (lineHeight / 2), lineWidth, lineHeight};
        DrawRectangleRec(horRoadLine, WHITE);
    }

    float getHeight() { return height; }
    float getWidth() { return width; }
    int getNbrRoads() { return nbrRoads; }
};

class TurnRoad : public Road
{
private:
    TurnType type;
    float startAngle;
    float endAngle;
    int nbrRoads;
    int segments;
    float innerRadius;
    float outerRadius;
    Vector2 center;

public:
    TurnRoad(float width, int segments, TurnType type, int nbr) : Road(width)
    {
        this->segments = segments;
        this->type = type;
        innerRadius = 100;
        outerRadius = innerRadius + width;

        switch (type)
        {
        case TL:
            startAngle = 180;
            endAngle = 270;
            break;

        case BL:
            startAngle = 90;
            endAngle = 180;
            break;

        case TR:
            startAngle = 270;
            endAngle = 360;
            break;

        case BR:
            startAngle = 0;
            endAngle = 90;
            break;
        default:
            startAngle = 180;
            endAngle = 270;
            break;
        }
    }

    void Draw(float xPos, float yPos)
    {
        switch (type)
        {
        case TL:
            center = {xPos + outerRadius, yPos};
            break;

        case BL:
            center = {xPos + outerRadius, yPos};
            break;

        case TR:
            center = {xPos, yPos + outerRadius};
            break;

        case BR:
            center = {xPos, yPos - outerRadius};
            break;
        default:
            center = {xPos + outerRadius, yPos};
            break;
        }

        DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, DARKGRAY);

        // DRAWING THE LINES
        float lineInnerRadius = outerRadius - width / 2 - width / 200;
        float lineOuterRadius = outerRadius - width / 2 + width / 200;

        float lineStartAngle = startAngle + 7.5;
        float lineEndAngle = lineStartAngle + 15;

        for (int i = 0; i < 3; i++)
        {
            DrawRing(center, lineInnerRadius, lineOuterRadius, lineStartAngle, lineEndAngle, segments, WHITE);
            lineStartAngle = lineEndAngle + 15;
            lineEndAngle = lineStartAngle + 15;
        }
    }

    float getInnerRadius() { return innerRadius; }
    float getOuterRadius() const { return outerRadius; }
    float getWidth() { return width; }
    int getNbrRoads() { return nbrRoads; }
    float getStartAngle() { return startAngle; }
    float getEndAngle() { return endAngle; }

    ~TurnRoad() {}
};

enum VehicleType
{
    CAR,
    BUS,
    MOTO,
    EMB
};
class Vehicle
{
private:
    float height;
    float width;
    float angle;
    Color color;
    VehicleType type;
    Rectangle carBody;
    Vector2 carOrigin;
    Rectangle carHead;
    Vector2 carHeadOrigin;
    // TESTING
    vector<Vector2> path;
    int pathIndex = 0;
    float moveSpeed = 300.0f;
    bool autoMode = true;
    bool active = true;

public:
    Vehicle(float xPos = 80, float yPos = 1200, Color color = RED, VehicleType type = CAR) : color(color)
    {
        this->angle = 0.0f;
        this->type = type;
        if (type == EMB)
        {
            width = 70;
            height = 100;
        }
        else if (type == BUS)
        {
            width = 70;
            height = 170;
        }
        else if (type == MOTO)
        {
            width = 40;
            height = 80;
        }
        else
        {
            width = 60;
            height = 90;
        }

        carBody = {xPos, yPos, width, height};
    }

    void Draw()
    {
        carOrigin = {carBody.width / 2, carBody.height};

        carHead = {carBody.x, carBody.y, carBody.width * 2 / 3, 20};
        carHeadOrigin = {carHead.width / 2, carBody.height + carHead.height / 2};

        DrawRectanglePro(
            carBody,
            carOrigin,
            angle,
            color);

        DrawRectanglePro(carHead, carHeadOrigin, angle, BLACK);
    }

    void Mouve(TrafficLight &light)
    {
        if (light.getState() != 0)
        {
            if (IsKeyDown(KEY_LEFT))
                angle -= 2; // 120 * dt; // rotate left
            if (IsKeyDown(KEY_RIGHT))
                angle += 2;

            // Convert angle to radians (needed for cos/sin)
            float rad = angle * DEG2RAD;

            // Forward
            if (IsKeyDown(KEY_UP))
            {
                carBody.x += sin(rad) * 5 /* speed * dt */;
                carBody.y -= cos(rad) * 5 /* speed * dt */;
            }
            // Backward
            if (IsKeyDown(KEY_DOWN))
            {
                carBody.x -= sin(rad) * 5 /* speed * dt */;
                carBody.y += cos(rad) * 5 /* speed * dt */;
            }
            // Strafe Right (slide right)
            if (IsKeyDown(KEY_D))
            {
                carBody.x += cos(rad) * 5 /* speed * dt */;
                carBody.y += sin(rad) * 5 /* speed * dt */;
            }
            // Strafe Left (slide left)
            if (IsKeyDown(KEY_A))
            {
                carBody.x -= cos(rad) * 5 /* speed * dt */;
                carBody.y -= sin(rad) * 5 /* speed * dt */;
            }
        }
    }

    // testing
    void SetPath(const vector<Vector2> &p)
    {
        path = p;
        pathIndex = 0;

        if (!path.empty())
        {
            carBody.x = path[0].x;
            carBody.y = path[0].y;
            // carBody.y = yPos;
        }
    }
    void ResetPath()
    {
        if (path.empty())
            return;

        pathIndex = 0;
        autoMode = true;

        carBody.x = path[0].x;
        carBody.y = path[0].y + 200;
    }
    void FollowPath(float dt, TrafficLight &light, const vector<Vehicle> &cars)
    {
        if (!autoMode || pathIndex >= path.size() - 1 || !active)
            return;

        Vector2 pos = {carBody.x, carBody.y};
        Vector2 next = path[pathIndex + 1];

        Vector2 dir = Vector2Normalize(Vector2Subtract(next, pos));
        Vector2 up = {0.0f, -1.0f};
        Vector2 down = {0.0f, 1.0f};

        if (light.getState() != 0)
        {
            // Move the car
            carBody.x += dir.x * moveSpeed * dt;
            carBody.y += dir.y * moveSpeed * dt;

            // Rotate the car to face direction
            angle = atan2(dir.x, -dir.y) * RAD2DEG;

            // If near the next point, go to the next
            if (Vector2Distance(pos, next) < 5.0f)
                pathIndex++;
        }

        // Stop at last point
        if (pathIndex >= path.size() - 1)
        {
            autoMode = false;
            // ResetPath();
        }
    }

    float getAngle() { return angle; }
    float getHeight() { return height; }
    float getWidth() { return width; }
    Vector2 getPosition() const { return {carBody.x, carBody.y}; }
    bool isAuto() { return autoMode; }
    bool isActive() { return active; }
    void setActive(bool mode) { active = mode; }

    ~Vehicle() {}
};

class Controller
{
private:
    float screenH;
    float screenW;
    int roadMap;
    vector<int> entryNodes;
    RoadGraph graph;

public:
    Controller(int roadNum) : roadMap(roadNum)
    {
        screenH = GetScreenHeight();
        screenW = GetScreenWidth();
    }
    void ClearGraph()
    {
        graph.ClearNodes();
        entryNodes.clear();
    }

    void DrawRoad1()
    {
        HorizontalRoad horiRoad(100, 200, 21);
        VerticalRoad vertRoad1(200, 100, 14);
        VerticalRoad vertRoad2(200, 100, 14);

        float xPos = GetScreenWidth() / 4 - vertRoad1.getWidth() / 2;
        float yPos = -vertRoad1.getHeight();

        for (int i = 0; i < vertRoad1.getNbrRoads(); i++)
        {
            vertRoad1.Draw(xPos, yPos);
            yPos += vertRoad1.getHeight();
        }

        xPos = (GetScreenWidth() / 4) * 3 - vertRoad1.getWidth() / 2;
        yPos = -vertRoad1.getHeight();

        for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
        {
            vertRoad2.Draw(xPos, yPos);
            yPos += vertRoad2.getHeight();
        }

        xPos = -horiRoad.getWidth() * 2;
        yPos = GetScreenHeight() / 2 - horiRoad.getHeight() / 2;

        for (int i = 0; i < horiRoad.getNbrRoads(); i++)
        {
            horiRoad.Draw(xPos, yPos);
            xPos += horiRoad.getWidth();
        }
    }
    void DrawRoad2()
    {
        VerticalRoad vertRoad1(200, 100, 7);
        TurnRoad turnTL(200, 20, TL, 1);
        HorizontalRoad horiRoad1(100, 200, 8);
        TurnRoad turnTR(200, 20, TR, 1);
        VerticalRoad vertRoad2(200, 100, 9);
        HorizontalRoad horiRoad2(100, 200, 7);

        float xPos = 80;
        float yPos = screenH;
        // Drawing vertical road 1
        for (int i = 0; i < vertRoad1.getNbrRoads(); i++)
        {
            yPos -= vertRoad1.getHeight();
            vertRoad1.Draw(xPos, yPos);
        }
        // Drawing TL road
        turnTL.Draw(xPos, yPos);

        xPos += turnTL.getOuterRadius();
        yPos -= horiRoad1.getHeight() + turnTL.getInnerRadius();
        // Drawing horizontal road 1
        for (int i = 0; i < horiRoad1.getNbrRoads(); i++)
        {
            horiRoad1.Draw(xPos, yPos);
            xPos += horiRoad1.getWidth();
        }

        //  Drawing the vertical road 2
        yPos += horiRoad1.getHeight();
        xPos += turnTR.getInnerRadius(); // for the virtual turn
        for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
        {
            vertRoad2.Draw(xPos, yPos);
            yPos += vertRoad2.getHeight();
        }

        // remake the older yPos to draw horiRoad2
        yPos -= horiRoad1.getHeight();
        xPos -= turnTR.getInnerRadius();
        for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
        {
            yPos -= vertRoad2.getHeight();
        }

        // Drawing the horizontal road 2
        for (int i = 0; i < horiRoad2.getNbrRoads(); i++)
        {
            horiRoad2.Draw(xPos, yPos);
            xPos += horiRoad1.getWidth();
        }
    }
    void DrawRoad3()
    {
        HorizontalRoad horiRoad1(100, 200, 8);
        HorizontalRoad horiRoad2(100, 200, 8);
        TurnRoad turnTL(200, 20, TL, 1);
        TurnRoad turnTR(200, 20, TR, 1);
        TurnRoad turnBR(200, 20, BR, 1);
        TurnRoad turnBL(200, 20, BL, 1);
        VerticalRoad vertRoad1(200, 100, 5);
        VerticalRoad vertRoad2(200, 100, 5);

        float xPos = -horiRoad1.getWidth();
        float yPos = screenH / 2 - horiRoad1.getHeight() / 2;

        // left hori road
        for (int i = 0; i < horiRoad1.getNbrRoads(); i++)
        {
            horiRoad1.Draw(xPos, yPos);
            xPos += horiRoad1.getWidth();
        }

        // // right hori road
        xPos += turnTL.getOuterRadius() * 2 - horiRoad2.getWidth() * 2;
        for (int i = 0; i < horiRoad2.getNbrRoads(); i++)
        {
            horiRoad2.Draw(xPos, yPos);
            xPos += horiRoad2.getWidth();
        }
        // remake position
        xPos -= turnTL.getOuterRadius() * 2 - horiRoad2.getWidth() * 2;
        for (int i = 0; i < horiRoad2.getNbrRoads(); i++)
        {
            xPos -= horiRoad2.getWidth();
        }

        xPos -= horiRoad1.getWidth();
        xPos += turnTL.getOuterRadius() - vertRoad1.getWidth() / 2;
        yPos -= turnTL.getOuterRadius() - vertRoad1.getHeight();

        for (int i = 0; i < vertRoad1.getNbrRoads(); i++)
        {
            vertRoad1.Draw(xPos, yPos);
            yPos -= vertRoad1.getHeight();
        }
        for (int i = 0; i < vertRoad1.getNbrRoads(); i++)
        {
            yPos += vertRoad1.getHeight();
        }

        yPos += turnTL.getOuterRadius() - vertRoad1.getHeight();
        yPos += horiRoad1.getHeight() / 2 + turnTL.getOuterRadius() - vertRoad2.getHeight();

        for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
        {
            vertRoad2.Draw(xPos, yPos);
            yPos += vertRoad2.getHeight();
        }
        for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
        {
            yPos -= vertRoad2.getHeight();
        }

        yPos -= turnTL.getOuterRadius() - vertRoad2.getHeight();
        xPos -= turnTL.getOuterRadius() - vertRoad1.getWidth() / 2;

        turnTL.Draw(xPos, yPos);
        xPos += turnTL.getOuterRadius();
        yPos -= turnTL.getOuterRadius();
        turnTR.Draw(xPos, yPos);
        yPos += turnTR.getOuterRadius() * 2;
        turnBR.Draw(xPos, yPos);
        xPos -= turnTL.getOuterRadius();
        yPos -= turnTL.getOuterRadius();
        turnBL.Draw(xPos, yPos);
    }

    void MapRoad1()
    {
        // ClearGraph();

        HorizontalRoad horiRoad(100, 200, 21);
        VerticalRoad vertRoad1(200, 100, 14);
        VerticalRoad vertRoad2(200, 100, 14);

        // Horizontal road
        int H0B = graph.AddNode({-100, screenH / 2 + 50});
        int H1B = graph.AddNode({screenW / 4 - 50, screenH / 2 + 50});
        int H2B = graph.AddNode({screenW / 4 + 50, screenH / 2 + 50});
        int H3B = graph.AddNode({screenW * 3 / 4 - 50, screenH / 2 + 50});
        int H4B = graph.AddNode({screenW * 3 / 4 + 50, screenH / 2 + 50});
        int H5B = graph.AddNode({screenW + 100, screenH / 2 + 50});

        int H0T = graph.AddNode({screenW + 100, screenH / 2 - 50});
        int H1T = graph.AddNode({screenW * 3 / 4 + 50, screenH / 2 - 50});
        int H2T = graph.AddNode({screenW * 3 / 4 - 50, screenH / 2 - 50});
        int H3T = graph.AddNode({screenW / 4 + 50, screenH / 2 - 50});
        int H4T = graph.AddNode({screenW / 4 - 50, screenH / 2 - 50});
        int H5T = graph.AddNode({-100, screenH / 2 - 50});

        // Vertical road 1
        int V1TR = graph.AddNode({screenW / 4 + 50, -100});
        int V1TL = graph.AddNode({screenW / 4 - 50, -100});
        int V1BR = graph.AddNode({screenW / 4 + 50, screenH + 100});
        int V1BL = graph.AddNode({screenW / 4 - 50, screenH + 100});
        int V1C = graph.AddNode({screenW / 4 + 50, screenH / 2});

        // Vertical road 2
        int V2TR = graph.AddNode({screenW * 3 / 4 + 50, -100});
        int V2TL = graph.AddNode({screenW * 3 / 4 - 50, -100});
        int V2BR = graph.AddNode({screenW * 3 / 4 + 50, screenH + 100});
        int V2BL = graph.AddNode({screenW * 3 / 4 - 50, screenH + 100});
        int V2C = graph.AddNode({screenW * 3 / 4, screenH / 2});

        // FIRST ENTRY CONNECTIONS
        graph.Connect(H0B, H1B);
        graph.Connect(H1B, H2B);
        graph.Connect(H2B, H3B);
        graph.Connect(H3B, H4B);
        graph.Connect(H4B, H5B);

        graph.Connect(H1B, V1BL);
        graph.Connect(H2B, V1TR);

        graph.Connect(H3B, V2BL);
        graph.Connect(H4B, V2TR);

        // SECOND ENTRY CONNECTIONS
        graph.Connect(H0T, H1T);
        graph.Connect(H1T, H2T);
        graph.Connect(H2T, H3T);
        graph.Connect(H3T, H4T);
        graph.Connect(H4T, H5T);

        graph.Connect(H1T, V2TR);
        graph.Connect(H2T, V2BL);

        graph.Connect(H3T, V1TR);
        graph.Connect(H4T, V1BL);

        graph.Connect(V1TL, H4T);
        graph.Connect(V2TL, H2T);

        graph.Connect(V1BR, H2B);
        graph.Connect(V2BR, H4B);

        entryNodes = {H0B, H0T, V1TL, V2TL, V1BR, V2BR};
    }
    void MapRoad2()
    {
        VerticalRoad vertRoad1(200, 100, 7);
        TurnRoad turnTL(200, 20, TL, 1);
        HorizontalRoad horiRoad1(100, 200, 8);
        TurnRoad turnTR(200, 20, TR, 1);
        VerticalRoad vertRoad2(200, 100, 9);
        HorizontalRoad horiRoad2(100, 200, 5);

        // Bottom road
        float xPos = 80 + vertRoad1.getWidth() / 4 * 3;
        float yPos = screenH + vertRoad1.getHeight();

        int V0R = graph.AddNode({xPos, yPos});
        int V1L = graph.AddNode({xPos - vertRoad1.getWidth() / 2, yPos});
        int V1R = graph.AddNode({xPos, yPos - vertRoad1.getHeight() * vertRoad1.getNbrRoads()});
        int V0L = graph.AddNode({xPos - vertRoad1.getWidth() / 2, yPos - vertRoad1.getHeight() * 7});

        float cxTurn = xPos + turnTL.getInnerRadius() + vertRoad1.getWidth() / 4;
        float cyTurn = yPos - vertRoad1.getHeight() * (vertRoad1.getNbrRoads() + 1);
        float arcRadius1 = turnTL.getInnerRadius() + turnTL.getWidth() / 4;

        int prevPointIndexBot = V1R;
        for (float a = turnTL.getStartAngle(); a <= turnTL.getEndAngle(); a += 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius1;
            float py = cyTurn + sin(rad) * arcRadius1;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexBot, VTR);
            prevPointIndexBot = VTR;
        }

        xPos = cxTurn;
        yPos = cyTurn - turnTL.getInnerRadius() - horiRoad1.getHeight() / 4;

        int H0B = graph.AddNode({xPos, yPos});
        int H3T = graph.AddNode({xPos + horiRoad1.getWidth(), yPos - horiRoad1.getHeight() / 2});

        xPos += horiRoad1.getWidth() * (horiRoad1.getNbrRoads() + 1) + horiRoad1.getWidth() / 2;

        int H1B = graph.AddNode({xPos, yPos});
        int H2T = graph.AddNode({xPos, yPos - horiRoad1.getHeight() / 2});

        int H2B = graph.AddNode({xPos + vertRoad2.getWidth() / 4 * 2, yPos});
        int H1T = graph.AddNode({xPos + vertRoad2.getWidth() / 4 * 2, yPos - horiRoad1.getHeight() / 2});

        int H3B = graph.AddNode({screenW + horiRoad1.getWidth(), yPos});
        int H0T = graph.AddNode({screenW + horiRoad1.getWidth(), yPos - horiRoad1.getHeight() / 2});

        int V2BL = graph.AddNode({xPos, screenH + vertRoad1.getHeight()});
        int V2BR = graph.AddNode({xPos + vertRoad2.getWidth() / 4 * 2, screenH + vertRoad1.getHeight()});

        // Top road

        float arcRadius2 = turnTL.getInnerRadius() + turnTL.getWidth() * 3 / 4;
        int prevPointIndexTop = H3T;
        for (float a = turnTL.getEndAngle(); a >= turnTL.getStartAngle(); a -= 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius2;
            float py = cyTurn + sin(rad) * arcRadius2;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexTop, VTR);
            prevPointIndexTop = VTR;
        }

        graph.Connect(V0R, V1R);
        graph.Connect(prevPointIndexBot, H1B);
        graph.Connect(H1B, H2B);
        graph.Connect(H2B, H3B);

        graph.Connect(H1B, V2BL);
        graph.Connect(V2BR, H2B);

        graph.Connect(H0T, H2T);
        graph.Connect(H0T, H1T);
        graph.Connect(V2BR, H1T);
        graph.Connect(H1T, H3T);
        graph.Connect(H2T, V2BL);
        graph.Connect(prevPointIndexTop, V1L);

        entryNodes = {V0R, V2BR, H0T};
    }
    void MapRoad3()
    {
        HorizontalRoad horiRoad1(100, 200, 8);
        HorizontalRoad horiRoad2(100, 200, 8);
        TurnRoad turnTL(200, 20, TL, 1);
        TurnRoad turnTR(200, 20, TR, 1);
        TurnRoad turnBR(200, 20, BR, 1);
        TurnRoad turnBL(200, 20, BL, 1);
        VerticalRoad vertRoad1(200, 100, 5);
        VerticalRoad vertRoad2(200, 100, 5);

        int H0BL = graph.AddNode({-100, screenH / 2 + 50});
        int H1BL = graph.AddNode({screenW / 2 - turnTL.getOuterRadius(), screenH / 2 + 50});
        int H0TL = graph.AddNode({-100, screenH / 2 - 50});
        int H1TL = graph.AddNode({screenW / 2 - turnTL.getOuterRadius(), screenH / 2 - 50});

        int H0TR = graph.AddNode({screenW + 100, screenH / 2 - 50});
        int H1TR = graph.AddNode({screenW / 2 + turnTL.getOuterRadius(), screenH / 2 - 50});
        int H0BR = graph.AddNode({screenW + 100, screenH / 2 + 50});
        int H1BR = graph.AddNode({screenW / 2 + turnTL.getOuterRadius(), screenH / 2 + 50});

        // Vertical road 1
        int V0TR = graph.AddNode({screenW / 2 + 50, -100});
        int V0TL = graph.AddNode({screenW / 2 - 50, -100});
        int V0BR = graph.AddNode({screenW / 2 + 50, screenH + 100});
        int V0BL = graph.AddNode({screenW / 2 - 50, screenH + 100});
        // int V1C = graph.AddNode({screenW / 4 + 50, screenH / 2});

        // Vertical road 2
        int V1TR = graph.AddNode({screenW / 2 + 50, screenH / 2 - turnTR.getOuterRadius()});
        int V1TL = graph.AddNode({screenW / 2 - 50, screenH / 2 - turnTR.getOuterRadius()});
        int V1BR = graph.AddNode({screenW / 2 + 50, screenH / 2 + turnTR.getOuterRadius()});
        int V1BL = graph.AddNode({screenW / 2 - 50, screenH / 2 + turnTR.getOuterRadius()});
        // int V2C = graph.AddNode({screenW * 3 / 4, screenH / 2});

        float cxTurn = screenW / 2;
        float cyTurn = screenH / 2;
        float arcRadius1 = turnBL.getInnerRadius() + turnBL.getWidth() / 4 * 3;

        int prevPointIndexBot = H1BL;
        for (float a = turnBL.getEndAngle() - 11; a >= turnBL.getStartAngle() + 11; a -= 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius1;
            float py = cyTurn + sin(rad) * arcRadius1;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexBot, VTR);
            prevPointIndexBot = VTR;
        }

        int prevPointIndexBot2 = prevPointIndexBot;
        int j = 0;
        for (float a = turnBR.getEndAngle() - 11; a >= turnBR.getStartAngle() + 11; a -= 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius1;
            float py = cyTurn + sin(rad) * arcRadius1;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexBot2, VTR);
            prevPointIndexBot2 = VTR;
            if (j == 0)
            {
                graph.Connect(V1BR, prevPointIndexBot2);
                j++;
            }
        }

        int prevPointIndexBot3 = prevPointIndexBot2;
        int i = 0;
        for (float a = turnTR.getEndAngle() - 11; a >= turnTR.getStartAngle() + 11; a -= 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius1;
            float py = cyTurn + sin(rad) * arcRadius1;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexBot3, VTR);
            prevPointIndexBot3 = VTR;
            if (i == 0)
            {
                graph.Connect(H1TR, prevPointIndexBot3);
                i++;
            }
        }

        int prevPointIndexBot4 = prevPointIndexBot3;
        int z = 0;
        for (float a = turnTL.getEndAngle() - 11; a >= turnTL.getStartAngle() + 11; a -= 3)
        {
            float rad = a * DEG2RAD;
            float px = cxTurn + cos(rad) * arcRadius1;
            float py = cyTurn + sin(rad) * arcRadius1;
            Vector2 point = {px, py};
            int VTR = graph.AddNode(point);
            graph.Connect(prevPointIndexBot4, VTR);
            prevPointIndexBot4 = VTR;
            if (z == 0)
            {
                graph.Connect(V1TL, prevPointIndexBot4);
                z++;
            }
        }

        graph.Connect(H0BL, H1BL);
        graph.Connect(prevPointIndexBot, V0BL);
        graph.Connect(prevPointIndexBot2, H0BR);
        graph.Connect(prevPointIndexBot3, V0TR);
        graph.Connect(prevPointIndexBot4, H0TL);

        graph.Connect(H0TR, H1TR);
        graph.Connect(V0TL, V1TL);
        graph.Connect(V0BR, V1BR);

        entryNodes = {H0BL, H0TR, V0TL, V0BR};
    }

    void setRoadMap(int num) { roadMap = num; }
    int getRoadMap() { return roadMap; }
    RoadGraph &getRoadGraph() { return graph; }
    vector<int> &getEntryNodes() { return entryNodes; }
};

int main()
{
    const int screenW = 1800, screenH = 1200;
    InitWindow(screenW, screenH, "Rainy Cinematic Traffic — Raylib (C++17)");
    SetTargetFPS(60);

    Controller controller(1);
    int roadMap = controller.getRoadMap();

    if (roadMap == 2)
    {
        controller.ClearGraph();
        controller.MapRoad2();
    }
    else if (roadMap == 3)
    {
        controller.ClearGraph();
        controller.MapRoad3();
    }
    else
    {
        controller.ClearGraph();
        controller.MapRoad1();
    }

    RoadGraph &graph = controller.getRoadGraph();
    vector<int> &entryNodes = controller.getEntryNodes();

    TrafficLight light(screenW / 4 - 150, screenH / 2 - 210);
    TrafficLight light2(screenW * 3 / 4 - 150, screenH / 2 - 210);

    vector<Vehicle> cars;

    // Checkbox states for car colors
    bool colorEnabled[6] = {true, true, true, true, true, true};
    const char *colorNames[6] = {"Red", "Blue", "Green", "Gray", "Pink", "Yellow"};

    vector<Color> carsColors = {RED, BLUE, DARKGREEN, GRAY, PINK, YELLOW};

    // Checkbox states for car types
    bool vehicleEnabled[4] = {true, true, false, true};
    const char *vehicleName[4] = {"CAR", "MOTO", "BUS", "EMB"};

    vector<VehicleType> vehicleTypes = {CAR, MOTO, BUS, EMB};

    int nbrOfCars = 0;
    int maxNbrOfCars = 5;

    vector<vector<Vector2>> paths;
    paths.resize(2);

    // // // TESTING CARS VECTOR
    float timer = 0;
    float carsInterval = 1.0f;

    bool showSidebar = false; // is the sidebar visible
    float screenMarg = 10;
    Rectangle sidebarButton = {screenMarg, screenMarg, 150, 50}; // top-left button
    int tempMaxCars = maxNbrOfCars;                              // temporary variable for sidebar selection
    const char *text = "Choose Max Number of Cars";

    bool tempColorEnabled[6];
    for (int i = 0; i < 6; i++)
        tempColorEnabled[i] = colorEnabled[i];

    // Pause Button
    Rectangle pauseBtn = {sidebarButton.x + sidebarButton.width + screenMarg, screenMarg, 100, 50};
    const char *pauseTxt = "Pause";

    // ------------------ MENU BEFORE SIMULATION ------------------
    bool startSimulation = false;
    while (!WindowShouldClose() && !startSimulation)
    {
        BeginDrawing();
        ClearBackground(GRAY);

        const char *title = "SmartCity Simulation";
        int titleFontSize = 60;
        int titleSize = MeasureText(title, titleFontSize);
        int x = (GetScreenWidth() - titleSize) / 2;
        int y = 300;

        DrawText(title, x, y, 60, WHITE);

        float startBtnWidht = 300;
        float startBtnHeight = 100;
        float startBtnXpos = GetScreenWidth() / 2 - startBtnWidht / 2;
        float startBtnYpos = GetScreenHeight() / 2 - startBtnHeight / 2;
        Rectangle startBtn = {startBtnXpos, startBtnYpos, startBtnWidht, startBtnHeight};
        DrawRectangleRec(startBtn, DARKGRAY);

        const char *start = "START";
        int startFontSize = 40;
        int startSize = MeasureText(start, startFontSize);
        int sX = (GetScreenWidth() - startSize) / 2;
        int sY = startBtnYpos + (startBtnHeight - startFontSize) / 2;

        DrawText(start, sX, sY, 40, WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, startBtn))
            {
                startSimulation = true;
            }
        }

        EndDrawing();
    }
    // ---------------- END MENU ------------------

    while (!WindowShouldClose())
    {
        if (roadMap != controller.getRoadMap())
        {
            controller.setRoadMap(roadMap);

            controller.ClearGraph();
            cars.clear();
            nbrOfCars = 0;

            if (roadMap == 1)
                controller.MapRoad1();
            else if (roadMap == 2)
                controller.MapRoad2();
            else
                controller.MapRoad3();
        }
        float dt = GetFrameTime();

        // car1.Mouve(light);
        // car1.FollowPath(dt, light);

        // // // TESTING CARS VECTOR
        timer += dt;
        if (timer >= carsInterval && nbrOfCars < maxNbrOfCars && pauseTxt == "Pause")
        {

            int startNode = entryNodes[GetRandomValue(0, entryNodes.size() - 1)];

            vector<Vector2> path = GeneratePath(graph, startNode);
            // Checking allawed colors
            vector<Color> allowedColors;
            for (int i = 0; i < carsColors.size(); i++)
            {
                if (colorEnabled[i])
                    allowedColors.push_back(carsColors[i]);
            }
            if (allowedColors.empty())
                allowedColors.push_back(RED);
            // Checking allawed vehicles
            vector<VehicleType> allowedTypes;
            for (int i = 0; i < vehicleTypes.size(); i++)
            {
                if (vehicleEnabled[i])
                    allowedTypes.push_back(vehicleTypes[i]);
            }
            if (allowedTypes.empty())
                allowedTypes.push_back(CAR);
            Color color = allowedColors[GetRandomValue(0, allowedColors.size() - 1)];
            // VehicleType type = static_cast<VehicleType>(GetRandomValue(0, 3));
            VehicleType type = allowedTypes[GetRandomValue(0, allowedTypes.size() - 1)];
            Vehicle newCar(80, screenH + 150, color, type);
            // vector<Vector2> randomPath = paths[GetRandomValue(0, paths.size() - 1)];
            newCar.SetPath(path);
            cars.push_back(newCar);

            timer = 0.0f;
            nbrOfCars++;
        }
        for (auto it = cars.begin(); it != cars.end();)
        {
            it->FollowPath(dt, light, cars);

            if (!it->isAuto())
            {
                it = cars.erase(it);
                nbrOfCars--;
            }
            else
            {
                ++it;
            }
        }

        light.Update(dt);
        light2.Update(dt);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Drawing first road plan
        /* {
            float xPos = 80;
            float yPos = screenH;
            // Drawing vertical road 1
            for (int i = 0; i < vertRoad1.getNbrRoads(); i++)
            {
                yPos -= vertRoad1.getHeight();
                vertRoad1.Draw(xPos, yPos);
            }
            // Drawing TL road
            turnTL.Draw(xPos, yPos);

            xPos += turnTL.getOuterRadius();
            yPos -= horiRoad1.getHeight() + turnTL.getInnerRadius();
            // Drawing horizontal road 1
            for (int i = 0; i < horiRoad1.getNbrRoads(); i++)
            {
                horiRoad1.Draw(xPos, yPos);
                xPos += horiRoad1.getWidth();
            }

            //  Drawing the vertical road 2
            yPos += horiRoad1.getHeight();
            xPos += turnTR.getInnerRadius(); // for the virtual turn
            for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
            {
                vertRoad2.Draw(xPos, yPos);
                yPos += vertRoad2.getHeight();
            }

            // remake the older yPos to draw horiRoad2
            yPos -= horiRoad1.getHeight();
            xPos -= turnTR.getInnerRadius();
            for (int i = 0; i < vertRoad2.getNbrRoads(); i++)
            {
                yPos -= vertRoad2.getHeight();
            }

            // Drawing the horizontal road 2
            for (int i = 0; i < horiRoad2.getNbrRoads(); i++)
            {
                horiRoad2.Draw(xPos, yPos);
                xPos += horiRoad1.getWidth();
            }
        }
 */
        // Drawing second road plan
        /* {
            float xPos = GetScreenWidth() / 4 - vertRoad1.getWidth() / 2;
            float yPos = -vertRoad3.getHeight();

            for (int i = 0; i < vertRoad3.getNbrRoads(); i++)
            {
                vertRoad3.Draw(xPos, yPos);
                yPos += vertRoad3.getHeight();
            }

            xPos = (GetScreenWidth() / 4) * 3 - vertRoad1.getWidth() / 2;
            yPos = -vertRoad3.getHeight();

            for (int i = 0; i < vertRoad4.getNbrRoads(); i++)
            {
                vertRoad4.Draw(xPos, yPos);
                yPos += vertRoad4.getHeight();
            }
        }
        {
            float xPos = -horiRoad3.getWidth() * 2;
            float yPos = GetScreenHeight() / 2 - horiRoad3.getHeight() / 2;

            for (int i = 0; i < horiRoad3.getNbrRoads(); i++)
            {
                horiRoad3.Draw(xPos, yPos);
                xPos += horiRoad3.getWidth();
            }
        } */

        if (roadMap == 2)
            controller.DrawRoad2();
        else if (roadMap == 3)
            controller.DrawRoad3();
        else
            controller.DrawRoad1();
        // // // TESTING CARS VECTOR
        for (auto &car : cars)
        {
            car.Draw();
        }
        light.Draw();
        light2.Draw();

        // ---------- Sidebar toggle button ----------
        DrawRectangleRec(sidebarButton, LIGHTGRAY);
        DrawText("Cars Menu", sidebarButton.x + 10, sidebarButton.y + 10, 20, BLACK);

        // ---------- Pause toggle button ----------
        DrawRectangleRec(pauseBtn, LIGHTGRAY);
        int pauseTxtSize = MeasureText(pauseTxt, 20);
        DrawText(pauseTxt, pauseBtn.x + (pauseBtn.width - pauseTxtSize) / 2, pauseBtn.y + pauseBtn.height / 3, 20, BLACK);

        // Check click on the sidebar button OR pause button
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            // sidbar
            if (CheckCollisionPointRec(mousePos, sidebarButton))
            {
                showSidebar = !showSidebar; // toggle sidebar
            }
            // pause
            if (CheckCollisionPointRec(mousePos, pauseBtn))
            {
                for (auto &car : cars)
                {
                    car.setActive(!car.isActive());
                }
                if (pauseTxt == "Pause")
                    pauseTxt = "Continue";
                else
                    pauseTxt = "Pause";
            }
        }
        if (showSidebar)
        {
            float fontSize = 30;
            // Sidebar background
            float sidebarPadding = 20;
            float sidebarX = screenMarg;
            float sidebarY = sidebarButton.y + sidebarButton.height + screenMarg;
            float sidebarW = 500;
            float sidebarH = screenH - sidebarY - screenMarg;
            Rectangle sidebar = {sidebarX, sidebarY, sidebarW, sidebarH};
            DrawRectangleRec(sidebar, sideColor);

            DrawText("OPTIONS", sidebarX + (sidebarW - MeasureText("OPTIONS", 40)) / 2, sidebarY + sidebarPadding, 40, BLACK);

            // sidebar ok Button
            float okBtnW = sidebarW - sidebarPadding * 2;
            float okBtnH = 80;
            float okBtnX = sidebarX + sidebarPadding;
            float okBtnY = screenH - okBtnH - screenMarg - sidebarPadding;
            Rectangle okButton = {okBtnX, okBtnY, okBtnW, okBtnH};
            // Draw OK button
            DrawRectangleRec(okButton, LIGHTGRAY);
            DrawText("OK", okButton.x + (okButton.width - MeasureText("OK", 40)) / 2, okButton.y + (okButton.height - 40) / 2, 40, WHITE);

            // Number of cars

            Rectangle moinsBtn = {okBtnX, sidebarY + 150, 50, 50};
            Rectangle plusBtn = {sidebarX + sidebarW - sidebarPadding - moinsBtn.width, moinsBtn.y, moinsBtn.width, moinsBtn.height};
            Rectangle nbrBox = {moinsBtn.x + moinsBtn.width + sidebarPadding, moinsBtn.y, plusBtn.x - (moinsBtn.x + moinsBtn.width + sidebarPadding * 2), moinsBtn.height};
            DrawText("Number of cars", sidebar.x + sidebarPadding, moinsBtn.y - sidebarPadding - 30, fontSize, BLACK);

            DrawRectangleRec(moinsBtn, LIGHTGRAY);
            DrawRectangleRec(plusBtn, LIGHTGRAY);
            DrawRectangleRec(nbrBox, {0, 0, 0, 100});

            DrawText("-", moinsBtn.x + (moinsBtn.width - MeasureText("-", fontSize)) / 2, moinsBtn.y + (moinsBtn.height - fontSize) / 2, fontSize, WHITE);
            DrawText("+", plusBtn.x + (plusBtn.width - MeasureText("+", fontSize)) / 2, plusBtn.y + (plusBtn.height - fontSize) / 2, fontSize, WHITE);
            DrawText(TextFormat("%d", maxNbrOfCars), nbrBox.x + (nbrBox.width - MeasureText("9", fontSize)) / 2, nbrBox.y + (nbrBox.height - fontSize) / 2, fontSize, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointRec(mousePos, moinsBtn))
                {
                    if (maxNbrOfCars > 0)
                        maxNbrOfCars--;
                }
                if (CheckCollisionPointRec(mousePos, plusBtn))
                {
                    if (maxNbrOfCars < 9)
                        maxNbrOfCars++;
                }
                if (CheckCollisionPointRec(mousePos, okButton))
                {
                    // maxNbrOfCars = tempMaxCars; // apply selection
                    showSidebar = false; // hide sidebar
                }
            }

            // Car colors

            float colorTxtY = moinsBtn.y + moinsBtn.height + sidebarPadding;
            DrawText("Vehicle colors :", sidebar.x + sidebarPadding, colorTxtY, fontSize, BLACK);

            float checkX = moinsBtn.x;
            float checkStartY = colorTxtY + fontSize + sidebarPadding;

            for (int i = 0; i < carsColors.size(); i++)
            {
                Rectangle box = {checkX, checkStartY + i * 50, 30, 30};

                // Draw checkbox
                DrawRectangleLinesEx(box, 2, BLACK);

                // If checked, draw a filled square
                if (colorEnabled[i])
                {
                    DrawRectangle(
                        box.x + 5,
                        box.y + 5,
                        box.width - 10,
                        box.height - 10,
                        carsColors[i]);
                }

                // Draw label
                DrawText(
                    colorNames[i],
                    box.x + box.width + sidebarPadding / 2,
                    box.y + 5,
                    fontSize,
                    BLACK);

                // Click detection
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePos = GetMousePosition();
                    if (CheckCollisionPointRec(mousePos, box))
                    {
                        colorEnabled[i] = !colorEnabled[i]; // toggle checkbox
                    }
                    else if (CheckCollisionPointRec(mousePos, okButton))
                    {

                        showSidebar = false;
                    }
                }
            }

            // Car type
            int TypesSize = MeasureText("Types", fontSize);
            float checkTypeX = sidebar.x + sidebar.width - sidebarPadding * 3 - TypesSize;
            float checkTypeY = checkStartY;
            DrawText("Types :", checkTypeX, colorTxtY, fontSize, BLACK);

            for (int i = 0; i < vehicleTypes.size(); i++)
            {
                Rectangle box = {checkTypeX, checkTypeY + i * 50, 30, 30};

                // Draw checkbox
                DrawRectangleLinesEx(box, 2, BLACK);

                // If checked, draw a filled square
                if (vehicleEnabled[i])
                {
                    DrawRectangle(
                        box.x + 5,
                        box.y + 5,
                        box.width - 10,
                        box.height - 10,
                        WHITE);
                }

                // Draw label
                DrawText(
                    vehicleName[i],
                    box.x + box.width + sidebarPadding / 2,
                    box.y + 5,
                    fontSize,
                    BLACK);

                // Click detection
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePos = GetMousePosition();
                    if (CheckCollisionPointRec(mousePos, box))
                    {
                        vehicleEnabled[i] = !vehicleEnabled[i]; // toggle checkbox
                    }
                }
            }

            // Road Map
            int RoadMapsSize = MeasureText("Road Maps", fontSize);
            float checkMapX = moinsBtn.x;
            float roadMapsTxtY = colorTxtY + fontSize + (carsColors.size() - 1) * 70;
            float checkMapY = roadMapsTxtY + fontSize + sidebarPadding;
            DrawText("Road Maps :", checkMapX, roadMapsTxtY, fontSize, BLACK);

            for (int i = 0; i < 3; i++)
            {
                Rectangle box = {checkMapX, checkMapY + i * 50, 30, 30};

                // Draw checkbox
                DrawRectangleLinesEx(box, 2, BLACK);

                // If checked, draw a filled square

                if (i + 1 == roadMap)
                {
                    DrawRectangle(
                        box.x + 5,
                        box.y + 5,
                        box.width - 10,
                        box.height - 10,
                        WHITE);
                }

                // Draw label
                DrawText(
                    TextFormat("Map %d", i + 1),
                    box.x + box.width + sidebarPadding / 2,
                    box.y + 5,
                    fontSize,
                    BLACK);

                // Click detection
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePos = GetMousePosition();
                    if (CheckCollisionPointRec(mousePos, box))
                    {
                        roadMap = i + 1; // toggle checkbox
                    }
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}