message = "Get the box over the barrier"

ship = {x=0, y=0}
box = {x=0, y=5}
floor = {x=0, y=10, w=10, h=1, btype="static"}
stick = {x = 2, y = 5, w = 0.25, h = 3, btype="static"}

objs = {box, floor, stick}

function won()
  return box.x > stick.x and math.abs(box.y - floor.y) < 3 and box.speed < 0.01
end

function lost()
  return box.health < 0
end
