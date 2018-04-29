import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.util.*;


public abstract class Order extends Entity {

    public int size;

    public Trader trader;

    public Position destination;

    public Order(Trader trader,int size){


        destination=Common.getInstance().plot.generateRandomDirection();

        this.trader=trader;
        this.size=size;

    }

}