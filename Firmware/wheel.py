def wheel_color(position):
    """Get color from wheel value (0 - 384)."""
    if position < 0:
        position = 0
    if position > 384:
        position = 384

    if position < 128:
        r = 127 - position % 128
        g = position % 128
        b = 0
    elif position < 256:
        g = 127 - position % 128
        b = position % 128
        r = 0
    else:
        b = 127 - position % 128
        r = position % 128
        g = 0

    return ((r << 16) | (g <<  8) | b)
	
print [ wheel_color(i) for i in range(384)]