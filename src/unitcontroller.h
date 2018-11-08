#ifndef UNIT_CONTROLLER_H
#define UNIT_CONTROLLER_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <String.hpp>
#include <Variant.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Array.hpp>
#include <InputEvent.hpp>


#include "unit.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>

#include <CoreTypes.hpp>
#include <InputMap.hpp>
#include <Sprite.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>
#include <AStar.hpp>
#include <Color.hpp>


namespace godot {
class UnitController : public godot::GodotScript<Node> {
	GODOT_CLASS(UnitController)
private:

	Vector3 vec_vec(Vector2 a);
	Vector2 vec_vec(Vector3 a);
	Vector3 vec_vec(Vector2 *a);
	//Vector2 vec_vec(Vector3 *a);
/**/
	//Array selected_units; //what the fug
	Array selected_units;

public:
	static void _register_methods();

	UnitController();
	~UnitController();
	/**/

	void _process(float delta);
	void _physics_process(float delta);
	void _ready();
	void _input(Variant event);
	//void _draw();

	Vector2 point_b;
	InputEvent *g_ie;

	void set_selected_units(Array u);
	void set_selected_units(Unit *u);
	Array get_selected_units();
	//static void

	//void look_under_cursor(InputEvent *ie);
	void spawn_raycast(float delta);
	void move_unit(InputEventMouseButton *iemb);
	void move_unit(Vector2 v, bool flag);
	void move_raycast(InputEvent *ie);


};
}
#endif
