import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;

public class Novice extends ConManDecorator {


    public Novice(ConMan decoratedConman) {

        super(decoratedConman);



    }

    @Override
    public void draw(Graphics2D g2d) {

        decoratedConman.draw(g2d);
        //do some extra stuff

        AffineTransform transform = g2d.getTransform();
        g2d.translate(getPosition().x,getPosition().y);
        //g2d.drawImage(pic,0,0,50,50,null);


        g2d.setColor(Color.ORANGE);
        g2d.fillRect(-25,-60,20,20);





        g2d.setTransform(transform);



    }

    @Override
    public void step(){

        decoratedConman.step();

    }

    public int getFortune(){

        return decoratedConman.getFortune();
    }

    @Override
    public Position getPosition(){

        return decoratedConman.getPosition();
    }

}