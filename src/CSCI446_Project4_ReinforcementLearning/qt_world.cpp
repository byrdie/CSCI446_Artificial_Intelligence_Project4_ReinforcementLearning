//class Gameboard : public QGraphicsView {
//public:

#include "qt_world.h"

using namespace std;

Qt_world::Qt_world(int num_tiles) {

    // Initialize variables
    N = num_tiles;
    win_sz = 1000;
    scale = win_sz / (num_tiles + 2);

    // Initialize Qt variables
    scene = new QGraphicsScene(0, 0, win_sz, win_sz);
    view = new World_view(scene);
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    view->resize(win_sz, win_sz);
    init_map();

}

void Qt_world::init_map() {
    wall_sprite = new QPixmap("sprites/cobble.png");
    start_sprite = new QPixmap("sprites/p_cobble.png");
    finish_sprite = new QPixmap("sprites/wall.png");
    track_sprite = new QPixmap("sprites/hero.png");
    car_sprite = new QPixmap("sprites/wumpus2.png");

    // Initialize map between bits and sprites
    sprite_map[WALL] = wall_sprite;
    sprite_map[START] = start_sprite;
    sprite_map[FINISH] = finish_sprite;
    sprite_map[TRACK] = track_sprite;
    sprite_map[CAR] = car_sprite;
    
  // Fill height map to know what elements to draw over
    height_map[WALL] = 1;
    height_map[START] = 1;
    height_map[FINISH] = 1;
    height_map[TRACK] = 1;
    height_map[CAR] = 2;

  


    // Construct map between indices and screen position
    for (int i = 0; i < N + 2; i++) {
        vector<Point*> ind2win_row;
        for (int j = 0; j < N + 2; j++) {
            ind2win_row.push_back(new Point(i* scale, j * scale));
        }
        ind2win.push_back(ind2win_row);
    }
}

QGraphicsPixmapItem * Qt_world::set_tile(int x, int y, int elem_bits) {

    QGraphicsPixmapItem * tile;
    int base = 0x00000001;
    for (int i = 0; i < 32; i++) {
        int new_base = base << i;
        int single_elem_bits = new_base & elem_bits;

        if (single_elem_bits != 0) {
            int z = height_map[single_elem_bits];
            QPixmap * base_sprite = sprite_map[single_elem_bits];
            QPixmap * sprite = new QPixmap(base_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
            tile = new QGraphicsPixmapItem(0, scene);
            tile->setPixmap(*sprite);
            tile->setPos(ind2win[x][y]->x, ind2win[x][y]->y);
            tile->setZValue(z);

        }

    }
    return tile;
}

void Qt_world::move_tile(QGraphicsPixmapItem * tile, int x, int y) {
    tile->setPos(ind2win[x][y]->x, ind2win[x][y]->y);
}

void Qt_world::save_world(char * filename) {
    scene->clearSelection(); // Selections would also render to the file
    //    scene->setSceneRect(scene->itemsBoundingRect()); // Re-shrink the scene to it's bounding contents
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32); // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent); // Start all pixels transparent

    QPainter painter(&image);
    scene->render(&painter);
    image.save(filename);
}

/**
 * The World View class exists to extend the QGraphicsView class. Its primary function
 * is to overwrite the keyPressEvents to provide input for human players
 * @param scene
 */


//World_view::World_view(QGraphicsScene * scene, Human_agent * h_agent) : QGraphicsView(scene) {
//    hagent = h_agent;
//}

World_view::World_view(QGraphicsScene * scene) : QGraphicsView(scene) {

}

void World_view::keyPressEvent(QKeyEvent * e) {


   

    QGraphicsView::keyPressEvent(e);
}

