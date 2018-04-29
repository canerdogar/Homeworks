import java.awt.*;
import java.util.*;

/**
 *
 */
public abstract class Entity {

    /**
     * Default constructor
     */
    public Entity() {
    }

    /**
     *
     */
    public Position position;

    /**
     *
     */
    public abstract void step();

    /**
     * @param g2d
     */
    public abstract void draw(Graphics2D g2d);

}