/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "tsage/scenes.h"
#include "tsage/tsage.h"
#include "tsage/staticres.h"
#include "tsage/ringworld2/ringworld2_scenes3.h"

namespace TsAGE {

namespace Ringworld2 {

/*--------------------------------------------------------------------------
 * Scene 3100 - 
 *
 *--------------------------------------------------------------------------*/
Scene3100::Scene3100() {
	_field412 = 0;
}

void Scene3100::synchronize(Serializer &s) {
	SceneExt::synchronize(s);

	s.syncAsSint16LE(_field412);
}

bool Scene3100::Actor6::startAction(CursorType action, Event &event) {
	if (action != CURSOR_TALK)
		return SceneActor::startAction(action, event);

	Scene3100 *scene = (Scene3100 *)R2_GLOBALS._sceneManager._scene;

	R2_GLOBALS._player.disableControl();
	scene->_sceneMode = 10;
	R2_GLOBALS._events.setCursor(CURSOR_CROSSHAIRS);
	scene->_stripManager.start(606, scene);
	return true;
}

void Scene3100::postInit(SceneObjectList *OwnerList) {
	if (R2_GLOBALS._sceneManager._previousScene == 1000) {
		if (R2_GLOBALS._player._oldCharacterScene[1] == 3100) {
			loadScene(3101);
			R2_GLOBALS._v58CE2 = 0;
		} else {
			loadScene(3100);
			g_globals->gfxManager()._bounds.moveTo(Common::Point(160, 0));
		}
	} else {
		loadScene(3100);
	}
	// Original was doing it twice in a row. Skipped.

	if (R2_GLOBALS._sceneManager._previousScene == 3255)
		R2_GLOBALS._v58CE2 = 0;

	SceneExt::postInit();
	_stripManager.addSpeaker(&_guardSpeaker);

	if (R2_GLOBALS._sceneManager._previousScene == -1)
		R2_GLOBALS._sceneManager._previousScene = 1000;

	R2_GLOBALS._player.postInit();
	R2_GLOBALS._player._characterIndex = R2_QUINN;
	R2_GLOBALS._player.disableControl();

	_actor1.postInit();
	_item2.setDetails(Rect(212, 97, 320, 114), 3100, 3, -1, -1, 1, NULL);
	_item1.setDetails(Rect(0, 0, 480, 200), 3100, 0, -1, -1, 1, NULL);
	_field412 = 0;

	if (R2_GLOBALS._sceneManager._previousScene == 1000) {
		if (R2_GLOBALS._player._oldCharacterScene[1] == 3100) {
			_sceneMode = 3102;
			_actor3.postInit();
			_actor4.postInit();
			_actor5.postInit();
			R2_GLOBALS._sound1.play(274);
			_sound1.fadeSound(130);
			setAction(&_sequenceManager, this, 3102, &_actor1, &R2_GLOBALS._player, &_actor3, &_actor4, &_actor5, NULL);
		} else {
			_actor6.postInit();
			_actor6.setup(3110, 5, 1);
			_actor6.changeZoom(50);
			_actor6.setPosition(Common::Point(10, 149));
			_actor6.setDetails(3100, 6, -1, -1, 2, NULL);

			_actor4.postInit();
			_actor4.setup(3103, 1, 1);
			_actor4.setPosition(Common::Point(278, 113));
			_actor4.setDetails(3100, 9, -1, -1, 2, NULL);
			_actor4.animate(ANIM_MODE_2, NULL);

			_field412 = 1;
			_actor1.setDetails(3100, 3, -1, -1, 2, NULL);
			R2_GLOBALS._sound1.play(243);
			R2_GLOBALS._sound2.play(130);
			_sceneMode = 3100;

			setAction(&_sequenceManager, this, 3100, &R2_GLOBALS._player, &_actor1, NULL);
		}
	} else if (R2_GLOBALS._sceneManager._previousScene == 3255) {
		_sceneMode = 3101;
		_actor2.postInit();
		_actor3.postInit();
		_field412 = 1;

		setAction(&_sequenceManager, this, 3101, &R2_GLOBALS._player, &_actor1, &_actor2, &_actor3, NULL);
	} else {
		_actor6.postInit();
		_actor6.setup(3110, 5, 1);
		_actor6.changeZoom(50);
		_actor6.setPosition(Common::Point(10, 149));
		_actor6.setDetails(3100, 6, -1, -1, 2, NULL);
		
		_actor4.postInit();
		_actor4.setup(3103, 1, 1);
		_actor4.setPosition(Common::Point(278, 113));
		_actor4.setDetails(3100, 9, -1, -1, 2, NULL);
		_actor4.animate(ANIM_MODE_2, NULL);

		_actor1.postInit();
		_actor1.setup(3104, 4, 1);
		_actor1.setPosition(Common::Point(143, 104));
		_actor1.setDetails(3100, 3, -1, -1, 2, NULL);

		R2_GLOBALS._player.setup(3110, 3, 1);
		R2_GLOBALS._player.changeZoom(50);
		R2_GLOBALS._player.animate(ANIM_MODE_1, NULL);
		R2_GLOBALS._player.setPosition(Common::Point(160, 150));
		R2_GLOBALS._player._moveDiff = Common::Point(3, 2);
		R2_GLOBALS._player.enableControl(CURSOR_ARROW);

		R2_GLOBALS._sound1.play(243);
	}
	
	R2_GLOBALS._player._oldCharacterScene[1] = 3100;
}

void Scene3100::remove() {
	R2_GLOBALS._scrollFollower = &R2_GLOBALS._player;
	R2_GLOBALS._sound1.fadeOut2(NULL);
	R2_GLOBALS._sound2.fadeOut2(NULL);
	_sound1.fadeOut2(NULL);
	SceneExt::remove();
}

void Scene3100::signal() {
	switch (_sceneMode) {
	case 10:
		warning("TODO: Unknown cursor used (6/-6)");
		R2_GLOBALS._player.enableControl();
		break;
	case 3100:
		R2_GLOBALS._player._moveDiff = Common::Point(3, 2);
		R2_GLOBALS._scrollFollower = &R2_GLOBALS._player;
		R2_GLOBALS._player.enableControl(CURSOR_ARROW);
		break;
	case 3101:
		R2_GLOBALS._sceneManager.changeScene(1000);
		break;
	case 3102:
		R2_GLOBALS._player._oldCharacterScene[1] = 1000;
		R2_GLOBALS._sceneManager.changeScene(1000);
		break;
	default:
		R2_GLOBALS._player.enableControl(CURSOR_ARROW);
		break;
	}
}

void Scene3100::dispatch() {
	if ((_sceneMode == 3100) && (_field412 != 0) && (R2_GLOBALS._player._position.y == 104)) {
		_field412 = 0;
		R2_GLOBALS._sound2.fadeOut2(NULL);
	}

	if ((_sceneMode == 3101) && (_field412 != 0) && (R2_GLOBALS._player._position.y < 104)) {
		_field412 = 0;
		_sound1.fadeSound(130);
	}

	Scene::dispatch();
}

/*--------------------------------------------------------------------------
 * Scene 3125 - Ghouls dormitory
 *
 *--------------------------------------------------------------------------*/
Scene3125::Scene3125() {
	_field412 = 0;
}

void Scene3125::synchronize(Serializer &s) {
	SceneExt::synchronize(s);

	s.syncAsSint16LE(_field412);
}

bool Scene3125::Item1::startAction(CursorType action, Event &event) {
	Scene3125 *scene = (Scene3125 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case CURSOR_USE:
		if (_useLineNum != -1)
			SceneItem::display(_resNum, _useLineNum, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	case CURSOR_LOOK:
		if (_lookLineNum != -1)
			SceneItem::display(_resNum, _lookLineNum, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	case CURSOR_TALK:
		if (_talkLineNum != -1)
			SceneItem::display(_resNum, _talkLineNum, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	default:
		warning("scene->display() called with two parameters");
		return scene->display(action);
		break;
	}

	return true;
}

bool Scene3125::Item2::startAction(CursorType action, Event &event) {
	Scene3125 *scene = (Scene3125 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case CURSOR_USE:
		R2_GLOBALS._player.disableControl();
		scene->_sceneMode = 3125;
		scene->setAction(&scene->_sequenceManager1, scene, 3125, &R2_GLOBALS._player, NULL);
		break;
	case CURSOR_LOOK:
		SceneItem::display(3125, 15, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	case CURSOR_TALK:
		SceneItem::display(3125, 13, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	default:
		return SceneHotspot::startAction(action, event);
		break;
	}

	return true;
}

bool Scene3125::Item3::startAction(CursorType action, Event &event) {
	Scene3125 *scene = (Scene3125 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case CURSOR_USE:
		R2_GLOBALS._player.disableControl();
		scene->_actor5.postInit();
		scene->_sceneMode = 3126;
		scene->setAction(&scene->_sequenceManager1, scene, 3126, &R2_GLOBALS._player, &scene->_actor2, &scene->_actor3, &scene->_actor4, &scene->_actor1, &scene->_actor5, NULL);
		break;
	case CURSOR_LOOK:
		SceneItem::display(3125, 9, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	case CURSOR_TALK:
		SceneItem::display(3125, 13, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		break;
	default:
		return SceneHotspot::startAction(action, event);
		break;
	}

	return true;
}

bool Scene3125::Actor1::startAction(CursorType action, Event &event) {
	Scene3125 *scene = (Scene3125 *)R2_GLOBALS._sceneManager._scene;

	if (action != CURSOR_USE)
		return SceneActor::startAction(action, event);

	R2_GLOBALS._player.disableControl();
	scene->_sceneMode = 3176;
	scene->setAction(&scene->_sequenceManager1, scene, 3176, &R2_GLOBALS._player, &scene->_actor1, NULL);
	return true;
}

void Scene3125::postInit(SceneObjectList *OwnerList) {
	loadScene(3125);
	SceneExt::postInit();
	_field412 = 0;

	_actor1.postInit();
	_actor1.setup(3175, 1, 1);
	_actor1.setPosition(Common::Point(35, 72));
	_actor1.setDetails(3125, 12, 13, -1, 1, NULL);

	_actor2.postInit();
	_actor2.setup(3126, 4, 1);
	_actor2.setPosition(Common::Point(71, 110));
	_actor2._numFrames = 20;

	_actor3.postInit();
	_actor3.setup(3126, 1, 1);
	_actor3.setPosition(Common::Point(215, 62));
	_actor3.fixPriority(71);

	_actor4.postInit();
	_actor4.setup(3126, 1, 1);
	_actor4.setPosition(Common::Point(171, 160));
	_actor4.fixPriority(201);
	
	_item3.setDetails(12, 3125, 9, 13, -1);
	_item2.setDetails(11, 3125, 15, 13, -1);
	_item1.setDetails(Rect(0, 0, 320, 200), 3125, 0, 1, 2, 1, NULL);

	R2_GLOBALS._sound1.play(262);
	R2_GLOBALS._player.postInit();

	if (R2_GLOBALS._player._oldCharacterScene[3] == 3250) {
		_sceneMode = 3175;
		setAction(&_sequenceManager1, this, 3175, &R2_GLOBALS._player, &_actor1, NULL);
	} else {
		R2_GLOBALS._player.setup(30, 5, 1);
		R2_GLOBALS._player.animate(ANIM_MODE_1, NULL);
		R2_GLOBALS._player.setPosition(Common::Point(89, 76));
		R2_GLOBALS._player.enableControl();
	}
	R2_GLOBALS._player._oldCharacterScene[3] = 3125;
}

void Scene3125::signal() {
	switch (_sceneMode) {
	case 3125:
		SceneItem::display(3125, 3, 0, 280, 1, 160, 9, 1, 2, 20, 7, 154, -999);
		_sceneMode = 3127;
		setAction(&_sequenceManager1, this, 3127, &R2_GLOBALS._player, NULL);
		break;
	case 3126:
		R2_GLOBALS.setFlag(79);
	// No break on purpose
	case 3176:
		R2_GLOBALS._sceneManager.changeScene(3250);
		break;
	default:
		R2_GLOBALS._player.enableControl();
		break;
	}
}

void Scene3125::dispatch() {
	if ((_sceneMode == 3126) && (_actor2._frame == 2) && (_field412 == 0)) {
		_field412 = 1;
		R2_GLOBALS._sound1.play(265);
	}
	Scene::dispatch();
}

/*--------------------------------------------------------------------------
 * Scene 3150 - Jail
 *
 *--------------------------------------------------------------------------*/
bool Scene3150::Item5::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case CURSOR_USE:
		if (R2_INVENTORY.getObjectScene(47) != 3150)
			return SceneHotspot::startAction(action, event);

		R2_GLOBALS._player.disableControl();
		scene->_sceneMode = 3154;
		scene->setAction(&scene->_sequenceManager, scene, 3154, &R2_GLOBALS._player, &scene->_actor3, NULL);
		return true;
	case R2_40:
		if ((R2_INVENTORY.getObjectScene(47) != 3150) && (R2_GLOBALS.getFlag(75))) {
			R2_GLOBALS._player.disableControl();
			scene->_actor3.postInit();
			scene->_actor3._effect = 3;
			scene->_actor3._shade = 5;
			scene->_sceneMode = 3155;
			scene->setAction(&scene->_sequenceManager, scene, 3155, &R2_GLOBALS._player, &scene->_actor3, NULL);
		} else {
			SceneItem::display(3150, 42, 0, 280, 1, 160, 9, 1, 2, 20, 7, 7, -999);
		}
		return true;
	default:
		return SceneHotspot::startAction(action, event);
		break;
	}
}

bool Scene3150::Item6::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case R2_41:
		R2_GLOBALS._player.disableControl();
		scene->_actor4.postInit();
		scene->_actor4._effect = 6;
		scene->_actor4._shade = 3;
		R2_GLOBALS._player.disableControl();
		scene->_sceneMode = 3158;
		scene->setAction(&scene->_sequenceManager, scene, 3158, &R2_GLOBALS._player, &scene->_actor4, NULL);
		return true;
	case R2_42:
		if ((R2_INVENTORY.getObjectScene(47) != 3150) && (R2_INVENTORY.getObjectScene(40) == 3150) && (R2_GLOBALS.getFlag(75))) {
			scene->_actor5.postInit();
			scene->_actor5._effect = 6;
			scene->_actor5._shade = 3;
			scene->_actor5.setDetails(3150, 30, -1, -1, 2, NULL);

			R2_GLOBALS._player.disableControl();
			scene->_sceneMode = 3159;
			scene->setAction(&scene->_sequenceManager, scene, 3159, &R2_GLOBALS._player, &scene->_actor5, NULL);
		} else {
			SceneItem::display(3150, 42, 0, 280, 1, 160, 9, 1, 2, 20, 7, 7, -999);
		}
	default:
		return SceneHotspot::startAction(action, event);
		break;
	}
}

bool Scene3150::Actor4::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	switch (action) {
	case CURSOR_USE:
		if (R2_GLOBALS.getFlag(75))
			return SceneActor::startAction(action, event);
		
		R2_GLOBALS._player.disableControl();
		scene->_sceneMode = 3151;
		scene->setAction(&scene->_sequenceManager, scene, 3151, &R2_GLOBALS._player, &scene->_actor4, NULL);
		return true;
	case R2_42:
		return false;
	default:
		return SceneActor::startAction(action, event);
		break;
	}
}

bool Scene3150::Actor5::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	if ((action != CURSOR_USE) || (R2_GLOBALS.getFlag(77)))
		return SceneActor::startAction(action ,event);

	R2_GLOBALS._player.disableControl();
	scene->_sceneMode = 3157;
	scene->setAction(&scene->_sequenceManager, scene, 3157, &R2_GLOBALS._player, &scene->_actor5, NULL);
	return true;
}

bool Scene3150::Actor6::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	if (action == CURSOR_USE) {
		if (R2_GLOBALS.getFlag(75)) {
			if (R2_GLOBALS.getFlag(77)) {
				R2_GLOBALS._player.disableControl();
				if (R2_GLOBALS.getFlag(76)) {
					scene->_sceneMode = 3152;
					scene->setAction(&scene->_sequenceManager, scene, 3152, &R2_GLOBALS._player, NULL);
				} else {
					scene->_sceneMode = 3153;
					scene->setAction(&scene->_sequenceManager, scene, 3152, &R2_GLOBALS._player, &scene->_actor4, NULL);
				}
			} else {
				SceneItem::display(3150, 42, 0, 280, 1, 160, 9, 1, 2, 20, 7, 7, -999);
			}
		} else {
			R2_GLOBALS._player.disableControl();
			scene->_sceneMode = 3152;
			scene->setAction(&scene->_sequenceManager, scene, 3152, &R2_GLOBALS._player, NULL);
		}
		return true;
	} else {
		return SceneActor::startAction(action, event);
	}
}

bool Scene3150::Actor7::startAction(CursorType action, Event &event) {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	if ((action == R2_43) && (!R2_GLOBALS.getFlag(80))) {
		R2_GLOBALS._player.disableControl();
		scene->_sceneMode = 3160;
		scene->setAction(&scene->_sequenceManager, scene, 3160, &R2_GLOBALS._player, &scene->_actor7, NULL);
		return true;
	}
	
	return SceneActor::startAction(action, event);
}

void Scene3150::Exit1::changeScene() {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	_enabled = false;
	g_globals->_events.setCursor(CURSOR_ARROW);
	R2_GLOBALS._player.disableControl();
	scene->_sceneMode = 11;

	Common::Point pt(-20, 180);
	NpcMover *mover = new NpcMover();
	R2_GLOBALS._player.addMover(mover, &pt, scene);
}

void Scene3150::Exit2::changeScene() {
	Scene3150 *scene = (Scene3150 *)R2_GLOBALS._sceneManager._scene;

	_enabled = false;
	g_globals->_events.setCursor(CURSOR_ARROW);
	R2_GLOBALS._player.disableControl();
	scene->_sceneMode = 12;

	scene->setAction(&scene->_sequenceManager, scene, 3163, &R2_GLOBALS._player, NULL);
}

void Scene3150::postInit(SceneObjectList *OwnerList) {
	loadScene(3150);
	if (R2_GLOBALS._sceneManager._previousScene == -1) {
		R2_INVENTORY.setObjectScene(35, 2000);
		R2_GLOBALS._player._oldCharacterScene[1] = 3100;
		R2_GLOBALS._player._oldCharacterScene[3] = 0;
		R2_GLOBALS._player._characterIndex = R2_MIRANDA;
	}
	SceneExt::postInit();

	if (R2_GLOBALS.getFlag(78)) {
		_exit1.setDetails(Rect(0, 135, 60, 168), EXITCURSOR_SW, 3275);
		_exit1.setDest(Common::Point(70, 125));
	}

	if (R2_GLOBALS.getFlag(80)) {
		_exit2.setDetails(Rect(249, 36, 279, 60), EXITCURSOR_NE, 3150);
		_exit2.setDest(Common::Point(241, 106));
	}

	R2_GLOBALS._player.postInit();
	R2_GLOBALS._player.disableControl();
	
	_actor2.postInit();
	_actor2.setPosition(Common::Point(64, 139));
	if (R2_GLOBALS.getFlag(78)) {
		_actor2.setup(3151, 1, 5);
		_actor2.fixPriority(125);
	} else {
		_actor2.setup(3151, 1, 1);
		_actor2.setDetails(3150, 8, -1, 9, 1, NULL);
	}

	if (R2_GLOBALS.getFlag(78)) {
		_actor1.postInit();
		_actor1.setup(3154, 1, 16);
		_actor1.setPosition(Common::Point(104, 129));
		_actor1._effect = 6;
		_actor1._shade = 3;
		_actor1.setDetails(3150, 24, -1, -1, -1, NULL);
	}

	_actor7.postInit();
	_actor7.setup(3154, 5, 1);
	if (R2_GLOBALS.getFlag(80))
		_actor7.setPosition(Common::Point(264, 108));
	else
		_actor7.setPosition(Common::Point(264, 58));
	_actor7.fixPriority(50);
	_actor7.setDetails(3150, 17, -1, 19, 1, NULL);

	if (R2_INVENTORY.getObjectScene(41) == 3150) {
		_actor4.postInit();
		if (R2_GLOBALS.getFlag(75)) {
			if (R2_GLOBALS.getFlag(76)) {
				R2_GLOBALS._walkRegions.enableRegion(1);
				R2_GLOBALS._walkRegions.enableRegion(4);
				R2_GLOBALS._walkRegions.enableRegion(5);
				R2_GLOBALS._walkRegions.enableRegion(6);
				_actor4.setup(3152, 4, 10);
				_actor4.setDetails(3150, 14, -1, -1, 1, NULL);
			} else {
				_actor4.setup(3152, 7, 4);
				_actor4.setDetails(3150, 13, -1, -1, 1, NULL);
			}
			_actor4.fixPriority(110);
			_actor4.setPosition(Common::Point(83, 88));
			_actor4._effect = 6;
			_actor4._shade = 3;
		} else {
			_actor4.setup(3152, 7, 3);
			_actor4.setPosition(Common::Point(143, 70));
			_actor4.setDetails(3150, 15, -1, -1, 1, NULL);
		}
	}

	if (R2_INVENTORY.getObjectScene(47) == 3150) {
		_actor3.postInit();
		_actor3.setup(3152, 7, 1);
		_actor3.setPosition(Common::Point(73, 83));
	}

	if (R2_INVENTORY.getObjectScene(40) == 3150) {
		_actor3.postInit();
		_actor3.setup(3152, 7, 3);
		_actor3.setPosition(Common::Point(70, 55));
		_actor3.fixPriority(111);
		_actor3._effect = 6;
		_actor3._shade = 5;
	}

	if (R2_INVENTORY.getObjectScene(42) == 3150) {
		_actor5.postInit();
		if (R2_GLOBALS.getFlag(77)) {
			_actor5.setup(3152, 7, 8);
			_actor5.setPosition(Common::Point(82, 92));
			_actor5.fixPriority(111);
			_actor5._effect = 6;
			_actor5._shade = 3;
		} else {
			_actor5.setup(3152, 7, 7);
			_actor5.setPosition(Common::Point(155, 79));
		}
		_actor5.setDetails(3150, 30, -1, -1, 2, NULL);
	}

	_actor6.postInit();
	_actor6.setup(3152, 7, 6);
	_actor6.setPosition(Common::Point(98, 73));
	_actor6.setDetails(3150, 43, -1, -1, 1, NULL);

	_item2.setDetails(12, 3150, 10, -1, 12);
	_item3.setDetails(Rect(186, 17, 210, 36), 3150, 6, -1, -1, 1, NULL);
	_item4.setDetails(Rect(61, 21, 92, 41), 3150, 7, -1, -1, 1, NULL);
	_item5.setDetails(Rect(63, 48, 78, 58), 3150, 6, -1, -1, 1, NULL);
	_item6.setDetails(Rect(63, 81, 100, 95), 3150, 3, 4, -1, 1, NULL);
	_item1.setDetails(Rect(0, 0, 200, 320), 3150, 0, 1, 2, 1, NULL);

	switch (R2_GLOBALS._player._oldCharacterScene[3]) {
	case 0:
		_sceneMode = 3150;
		_actor1.postInit();
		_actor1._effect = 6;
		_actor1._shade = 5;
		setAction(&_sequenceManager, this, 3150, &R2_GLOBALS._player, &_actor1, &_actor2, NULL);
		break;
	case 1200:
		_sceneMode = 3162;
		setAction(&_sequenceManager, this, 3162, &R2_GLOBALS._player, NULL);
		break;
	case 3275: {
		_sceneMode = 10;
		R2_GLOBALS._player.setup(30, 3, 1);
		R2_GLOBALS._player.animate(ANIM_MODE_1, NULL);
		R2_GLOBALS._player.setPosition(Common::Point(-20, 180));
		R2_GLOBALS._player._moveDiff = Common::Point(3, 2);

		Common::Point pt(80, 125);
		NpcMover *mover = new NpcMover();
		R2_GLOBALS._player.addMover(mover, &pt, this);
		break;
		}
	default:
		if ((R2_GLOBALS._v56AA0 == 1) && (R2_INVENTORY.getObjectScene(35) == 2000) && (R2_GLOBALS._player._oldCharacterScene[1] == 3100)) {
			++R2_GLOBALS._v56AA0;
			_sceneMode = 3156;
			_actor1.postInit();
			_actor1._effect = 6;
			_actor1._shade = 3;

			_actor2.postInit();
			_actor5.postInit();
			_actor5._effect = 6;
			_actor5._shade = 3;
				
			setAction(&_sequenceManager, this, 3156, &R2_GLOBALS._player, &_actor1, &_actor2, &_actor5, NULL);
		} else {
			if (R2_GLOBALS._v56AA0 != 2)
				++R2_GLOBALS._v56AA0;

			R2_GLOBALS._player.setup(30, 3, 1);
			R2_GLOBALS._player.animate(ANIM_MODE_1, NULL);
			R2_GLOBALS._player.setPosition(Common::Point(155, 120));
			R2_GLOBALS._player._moveDiff = Common::Point(3, 2);
			R2_GLOBALS._player.enableControl();
		}
	}

	R2_GLOBALS._player._oldCharacterScene[3] = 3150;
}

void Scene3150::signal() {
	switch (_sceneMode) {
	case 11:
		R2_GLOBALS._sceneManager.changeScene(3275);
		break;
	case 12:
		R2_GLOBALS._sceneManager.changeScene(1200);
		break;
	case 3151:
		_actor1.remove();
		R2_INVENTORY.setObjectScene(41, 3);
		R2_GLOBALS._player.enableControl();
		break;
	case 3153:
		R2_GLOBALS.setFlag(76);
		_actor4.setDetails(3150, 14, -1, -1, 3, NULL);
		_actor1.postInit();
		_actor1.setDetails(3150, 24, -1, -1, 2, NULL);
		_sceneMode = 3161;
		setAction(&_sequenceManager, this, 3161, &_actor1, &_actor2, NULL);
		break;
	case 3154:
		_actor3.remove();
		R2_INVENTORY.setObjectScene(47, 3);
		R2_GLOBALS._player.enableControl();
		break;
	case 3155:
		R2_INVENTORY.setObjectScene(40, 3150);
		R2_GLOBALS._player.enableControl();
		break;
	case 3156:
		_actor5.setDetails(3150, 30, -1, -1, 2, NULL);
		R2_INVENTORY.setObjectScene(42, 3150);
		R2_GLOBALS._player.enableControl();
		break;
	case 3157:
		_actor5.remove();
		R2_INVENTORY.setObjectScene(42, 3);
		R2_GLOBALS._player.enableControl();
		break;
	case 3158:
		R2_GLOBALS.setFlag(75);
		R2_INVENTORY.setObjectScene(41, 3150);
		_actor4.fixPriority(110);
		_actor4.setDetails(3150, 13, -1, -1, 2, NULL);
		R2_GLOBALS._player.enableControl();
		break;
	case 3159:
		R2_GLOBALS.setFlag(77);
		R2_INVENTORY.setObjectScene(42, 3150);
		R2_GLOBALS._player.enableControl();
		break;
	case 3160:
		R2_INVENTORY.setObjectScene(52, 3150);
		R2_GLOBALS.setFlag(80);
		R2_GLOBALS._sceneManager.changeScene(1200);
		break;
	case 3161:
		R2_GLOBALS._sceneItems.remove(&_actor2);
		_exit1.setDetails(Rect(0, 135, 60, 168), EXITCURSOR_SW, 3275);
		_exit1.setDest(Common::Point(70, 125));
		R2_GLOBALS._walkRegions.enableRegion(1);
		R2_GLOBALS._walkRegions.enableRegion(4);
		R2_GLOBALS._walkRegions.enableRegion(5);
		R2_GLOBALS._walkRegions.enableRegion(6);
		R2_GLOBALS.setFlag(78);
		R2_GLOBALS._player.enableControl();
		break;
	default:
		R2_GLOBALS._player.enableControl();
		break;
	}
}

void Scene3150::dispatch() {
	if (_actor5._position.x == 155) {
		_actor5._effect = 0;
		_actor5._shade = 0;
	}

	if (_actor1._visage == 3154) {
		_actor1._effect = 0;
		_actor1._shade = 0;
	}

	Scene::dispatch();
}

} // End of namespace Ringworld2
} // End of namespace TsAGE
