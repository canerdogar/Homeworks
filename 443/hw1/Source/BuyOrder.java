import java.awt.*;
import java.awt.geom.AffineTransform;

public class BuyOrder extends Order {

    public BuyOrder(Trader trader,int size) {
        super(trader,size);
    }

    @Override
    public void draw(Graphics2D g2d){

        AffineTransform transform = g2d.getTransform();
        g2d.setColor(Color.GREEN);
        g2d.translate(this.position.x, this.position.y);
        //g2d.setStroke(new BasicStroke(3.0f));
        g2d.fillOval(0, -18, 20, 20);

        String[] ns=trader.name.split(" ");
        g2d.drawString(""+ns[0].charAt(0) + ns[1].charAt(0), 0, -24);

        g2d.setColor(Color.BLACK);
        g2d.drawString(""+size, 6, -6);



        g2d.setTransform(transform);

    }

    @Override
    public void step(){
        Position direction=Position.getUnit(position,destination);
        double step=-5.0;
        position= new Position(direction.x * step + position.x, direction.y * step + position.y);

    }


}