extends EcsNode


# Declare member variables here. Examples:
var playerStartingPos = Vector2(50, 450)


# Called when the node enters the scene tree for the first time.
func _ready():
	setEntityPosition(0, playerStartingPos)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
