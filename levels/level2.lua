message = "Make the box go fast"

ship = {x=0, y=-10}
box = {x=0, y=7}
floor = {x=0, y=10, w=10, h=1, btype="static"}

objs = {box, floor}

function won()
  return box.speed > 8.0
end

function lost()
  return box.health < 0
end
