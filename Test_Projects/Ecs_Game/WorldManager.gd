extends EcsNode


# Declare member variables here. Examples:
var playerStartPos = Vector2(50, 500)
var playerCurrentPos = Vector2(50, 500)
var playerMoveIncrement = Vector2(10, 0)


# Called when the node enters the scene tree for the first time.
func _ready():
	playerCurrentPos = playerStartPos
	setEntityPosition(0, playerCurrentPos)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	playerCurrentPos += playerMoveIncrement
	setEntityPosition(0, playerCurrentPos)
	pass

func _draw():
	pass
