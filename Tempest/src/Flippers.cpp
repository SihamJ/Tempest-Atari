#include "Flippers.hpp"

Flippers::Flippers(){}

//constructeur
Flippers::Flippers(std::string&& name)
{
    this->name = std::move(name);
}

Flippers::Flippers(std::string&& name, Color&& c)
    : Enemy(std::move(c))
{
    this->name = std::move(name);
}

//constructeur
Flippers::Flippers(std::string&& name,  Point&& center,  Tunel&& h)
    : Enemy(std::move(center), std::move(h))
{
    this->name = std::move(name);
}

// copy constructor
Flippers::Flippers(const Flippers &other) 
    : Enemy(other)
{ 
    this->name = static_cast<std::string>("Flippers");
}

Flippers::Flippers(Flippers &&other)
    : Enemy(std::move(other))
{
    this->name = static_cast<std::string>("Flippers");
    this->width = 57;
    this->height = 64;
}

//destructeur
Flippers::~Flippers(){}


void Flippers::set_tunnel( Tunel&& h) { this->hall = h; }




void Flippers::set_next_hall(Tunel &&h){
    this->next_hall = h;
}

void Flippers::set_current_angle(double angle){
    this->current_angle = angle;
}

void Flippers::set_next_angle(double angle){
    this->next_angle = angle;
}

void Flippers::set_flipping(bool flipping){
    this->isFlipping = flipping;
}

void Flippers::set_flip_center(Point p){
    this->flip_center = p;
}

const Tunel Flippers::get_next_hall() const {
    return this->next_hall;
}

const double Flippers::get_current_angle() const{
    return this->current_angle;
}

const int Flippers::get_state() const {
    return this->state;
}

const bool Flippers::will_flip() {
    std::mt19937 gen(this->rd());
    std::uniform_int_distribution<int> rand (0, 5);
    
    return rand(gen) == 0 ? true : false;
}

const bool Flippers::flipping() const{
    return this->isFlipping;
}

const bool Flippers::shoot() {

    std::mt19937 gen(this->rd());
    std::uniform_int_distribution<int> rand (0, 8);
    
    return rand(gen) == 0 ? true : false;
}

void Flippers::set(Tunel&& h){

        std::mt19937 gen(this->rd());
        std::uniform_real_distribution<double> rand (0.25, 0.85);

        this->random_p = rand(gen);
        
    
        this->hall = h;

        double dist = h.get_small_line().get_p0().euclideanDistance(h.get_small_line().get_p1());
        this->width = dist;
        this->height = static_cast<double>(init_height) * ( static_cast<double>(width) / static_cast<double>(init_width));
        this->random_p = 1;
        //this->random_p -= this->height / (2 * this->hall.get_small_line().inLine(0.5).euclideanDistance(this->hall.get_big_line().inLine(0.5)));

        Point centre_small_line { std::move( hall.get_small_line().inLine(0.5))};
        this->center = centre_small_line;
        this->flip_center = Point(this->width/2, this->height/2);

        Point centre_big_line { std::move( hall.get_big_line().inLine(0.5))};

        x = centre_small_line.get_x() - ( static_cast<double>(width)/2.0);
        y = centre_small_line.get_y() - ( static_cast<double>(height)/2.0);

        this->angle = this->hall.get_angle();
        this->current_angle = this->angle;
        this->start = this->hall.get_small_line();

        this->hall = h;
        this->state = 0;

        // On calcule la ligne limit de déplacement du flipper (parallèle à big line)
        Point sp0 { std::move( this->hall.get_small_line().get_p0())};
        Point sp1 { std::move( this->hall.get_small_line().get_p1())};
        Point bp0 { std::move( this->hall.get_big_line().get_p0())};
        Point bp1 { std::move( this->hall.get_big_line().get_p1())};

        long double segment1 = this->random_p * (sp0.euclideanDistance(bp0));
        long double segment2 = this->random_p * (sp1.euclideanDistance(bp1));
        Line l1 { std::move( Line(sp0, bp0))};
        Line l2 { std::move( Line(sp1, bp1))};

        Point pp0 { std::move( l1.inLine(segment1 / l1.length()))};
        Point pp1 { std::move( l2.inLine(segment2 / l2.length()))};

        this->limit_init.set_points({pp0, pp1});
        this->dest = Line(limit_init);

        // this->limit_init = this->hall.get_big_line();
        // this->dest = Line(this->limit_init);
    }


bool Flippers::get_closer(long double h) {

    Point c = hall.get_small_line().inLine(0.5);
    double r = (static_cast<double>(this->height)/2.) / this->hall.get_big_line().inLine(0.5).euclideanDistance(this->hall.get_small_line().inLine(0.5));


    // Si le flipper est arrivé à sa destination, on passe à l'état 1 (mode flip)
    if(this->state == 0 && this->center == this->limit_init.inLine(0.5))
    {
        this->state = 1;
        this->isFlipping = false;
        return intersect(this->hall.get_big_line());
    }

    if(this->state == 0) {

        this->center = Line(this->center, this->dest.inLine(0.5)).inLine(h*h*std::cbrtl(h));
        this->width = h * this->limit_init.length();
        this->height = static_cast<long double>(init_height) * ( static_cast<long double>(width) / static_cast<long double>(init_width));
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
        this->flip_center = Point(this->width/2, this->height/2);
        return intersect(this->hall.get_big_line());
    }

    else if(this->isFlipping) {
        this->hall = Tunel(this->next_hall);
        this->width = this->hall.get_big_line().length() * 0.8;
        this->height = this->width / 2;
        this->center = Point(this->hall.get_big_line().inLine(0.5).get_x()+width/2, this->hall.get_big_line().inLine(0.5).get_y()-height);
        this->x = this->center.get_x() - ( static_cast<long double>(this->width)/2.0);
        this->y = this->center.get_y() - ( static_cast<long double>(this->height)/2.0);
        this->flip_center = Point(this->width/2, this->height/2);
        this->isFlipping = false;
    }

    return intersect(this->hall.get_big_line());
}

bool Flippers::intersect(Line l) {

    SDL_Rect r = {static_cast<int>(this->x), static_cast<int>(this->y), static_cast<int>(this->width), static_cast<int>(this->height)};

    int x1 = l.get_p0().get_x();
    int y1 = l.get_p0().get_y();
    int x2 = l.get_p1().get_x();
    int y2 = l.get_p1().get_y();

    // printf("%d %d %d %d %d %d %d %d \n", this->x, this->y, this->width, this->height, x1, y1, x2, y2);

    return SDL_IntersectRectAndLine(&r, &x1, &y1, &x2, &y2);
}

void Flippers::draw(std::shared_ptr<SDL_Renderer> renderer) {
    std::string path;
    path = static_cast<std::string>("images/flipper_") + this->color.get_name() + static_cast<std::string>(".bmp"); 

    if(render_image(renderer, path, this->init_width, this->init_height, this->width, this->height, static_cast<const int>(x),  static_cast<const int>(y), 
                    this->current_angle, this->flip_center.get_point())){
        std::cout << "Can't load flipper image" <<std::endl;
        return;
    }
}