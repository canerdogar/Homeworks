import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.*;

public abstract class ConMan extends Entity {

    public String fileName;
    public String name;
    public State state;
    public BufferedImage pic;
    public int fortune=0;
    public int timeToChange=50;
    public Position direction;
    public int x=-25,y=-25;
    public int shakeDirection=0;

    public ConMan(){



    }

    public ConMan(String fileName,String name) {

        Random rand=new Random();
        int x=rand.nextInt(Common.getInstance().windowWidth-40)+20;
        int y=rand.nextInt((3*Common.getInstance().windowHeight) /10 - 60)+ (Common.getInstance().windowHeight/5) + 20;
        position=new Position(x,y);

        //System.out.println(fileName);
        this.fileName=fileName;
        this.name=name;

        try {
            //System.out.println(fileName);
            pic = ImageIO.read(new File(this.fileName));
        }
        catch(Exception e) {
            e.printStackTrace();
        }


        this.state=new ChaseClosest();
    }


    public abstract int getFortune();

    public abstract Position getPosition();


}