extends MouseImageNode


# Declare member variables here. Examples:
var theTexture = load("res://crosshair.jpg")

# Called when the node enters the scene tree for the first time.
func _ready():
	setTexture(theTexture)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
#	print("x ", getMousePos().x, " y ", getMousePos().y)
	pass
