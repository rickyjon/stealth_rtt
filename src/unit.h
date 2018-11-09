#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <String.hpp>
#include <Variant.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Array.hpp>
#include <AStar.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseButton.hpp>

struct gun_attr {
	bool supressed;
	bool hitscan;

	bool generic_ammo;
	unsigned int ammo;
	unsigned int current_ammo;
	unsigned int max_ammo;

	unsigned int range;
	unsigned int rof;
};
/*
struct area {
	area *parent;
	int f_cost;
	int h_cost;
	int g_cost;
	bool traversable;
};
*/
namespace godot {
class Unit : public godot::GodotScript<Area2D> {
	GODOT_CLASS(Unit)
private:

	Vector3 vec_vec(Vector2 a);
	Vector2 vec_vec(Vector3 a);
	Vector3 vec_vec(Vector2 *a);
	Vector2 vec_vec(Vector3 *a);

public:
	static void _register_methods();

	//complex data
	Array open_arr = Array();
	Array closed_arr;
	Vector2 point_b;

	//simple data
	bool selected;

	Unit();
	~Unit();

	void _process(float delta);
	void _ready();
	void _input(Variant event);
	void _draw();

	//functions
	void move_camera_unit(int i);
	void move_to(float delta, Vector2 point_b);
	void find_path();
	void get_move_cursor_position();

	void area_entered(Variant a);

	//astar func
	AStar *as;
	int astar_calculate_point_index(Vector2 *point, Vector2 *map_boundry);
	bool astar_out_of_bounds(Vector2 vec, Array map_boundry) ;

	void get_points(AStar *as);
	void astar_add_walk_cells(AStar *as, Array obstacle_array);
	Array astar_con_walk_cells(AStar *as, Array point_array);
	Array astar_add_unwalk_cells(Array map_boundries);

	//virtual

	virtual void action_1();
	virtual void action_2();
	virtual void action_3();
	virtual void action_4();
	/*
	virtual void action_5();
	*/
	//virtual void action_6() = 0;

	//returning functions
	//AStar get_points(AStar *as);

};
}
#endif
