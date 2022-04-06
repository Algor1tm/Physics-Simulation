#include "../../include/objects/Polygon.hpp"


Polygon::Polygon(std::vector<Vector2d> points, int Thickness){
    MaxPoint = MinPoint = points[0];
    OutLineThickness = Thickness;

    for(unsigned i = 0; i < points.size(); i++){
        if(i == points.size() - 1)
            lines.push_back(new Line(points[i], points[0], OutLineThickness));
        else
            lines.push_back(new Line(points[i], points[i + 1], OutLineThickness));

        if(points[i].x > MaxPoint.x)
            MaxPoint.x = points[i].x;
        if(points[i].y > MaxPoint.y)
            MaxPoint.y = points[i].y;
        if(points[i].x < MinPoint.x)
            MinPoint.x = points[i].x;
        if(points[i].y < MinPoint.y)
            MinPoint.y = points[i].y;
    }
    MaxPoint += Vector2d(OutLineThickness / 2, OutLineThickness / 2);
    MinPoint -= Vector2d(OutLineThickness / 2, OutLineThickness / 2);

}

bool Polygon::isNear(Ball* ball){
    float r = ball->getRadius();
    Vector2d p = ball->getPos();

    return p.x <= (MaxPoint.x + r) && p.y <= (MaxPoint.y + r) && p.x >= (MinPoint.x - r) && p.y >= (MinPoint.y - r);
}

void Polygon::Draw(sf::RenderWindow* wnd){
    for(auto line: lines)
        line->Draw(wnd);

}

Polygon::~Polygon(){
    for(auto line: lines)
        delete line;
    lines.clear();
}
