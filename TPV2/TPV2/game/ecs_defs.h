// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class KeyBoardCtrl;
class Bounce;
class Image;
class Rotate;
class deAcceleration;
class Health;
class FighterCtrl;
class GameCtrl;
class Gun;
class ShowAtOppositeSide;
class FramedImage;
class DisableOnExit;
class State;
class CollisionManager;
class Follow;
class Generations;
class AsteroidsManager;

#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	KeyBoardCtrl,\
	Bounce,\
	Image,\
	Rotate,\
	deAcceleration,\
	Health,\
	FighterCtrl,\
	GameCtrl,\
	Gun,\
	ShowAtOppositeSide,\
	FramedImage,\
	DisableOnExit,\
	State,\
	CollisionManager,\
	Follow,\
	Generations,\
	AsteroidsManager

// groups

struct Vidas;
struct Balas;
struct Asteroids;

#define _GRPS_LIST_  Vidas,\
	Balas,\
	Asteroids

// handlers
struct Nave;
#define _HDLRS_LIST_ Nave

// systems
class GameCtrlSystem;
class FighterSystem;
class RenderSystem;
class BulletSystem;
class AsteroidsSystem;

#define _SYS_LIST_ GameCtrlSystem,\
	FighterSystem,\
	RenderSystem,\
	BulletSystem, \
	AsteroidsSystem

