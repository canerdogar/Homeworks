import java.awt.*;
import java.awt.geom.AffineTransform;

public class BasicConMan extends ConMan {

    public BasicConMan(String fileName,String name) {
        super(fileName,name);
    }




    @Override
    public void draw(Graphics2D g2d){

        AffineTransform transform = g2d.getTransform();
        g2d.translate(position.x, position.y);
        g2d.drawImage(pic,x,y,50,50,null);

        g2d.setColor(Color.BLUE);
        if(state.getClass().getName().equals("Rest")){
            g2d.drawString("Rest",-20,40);
        }else if(state.getClass().getName().equals("Shake")){
            g2d.drawString("Shake",-20,40);
        }else if(state.getClass().getName().equals("GotoXY")){
            g2d.drawString("GotoXY",-20,40);
        }else if(state.getClass().getName().equals("ChaseClosest")){
            g2d.drawString("ChaseClosest",-20,40);
        }

        g2d.setColor(Color.BLACK);
        g2d.drawString(name,-25,-25);

        g2d.setColor(Color.RED);
        g2d.drawString(""+fortune,-20,60);

        g2d.setTransform(transform);

    }

    @Override
    public void step(){

        state.step(this);

    }

    @Override
    public int getFortune(){

        return fortune;

    }

    @Override
    public Position getPosition(){

        return position;
    }

}