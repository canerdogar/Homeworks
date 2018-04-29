import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.*;
import javax.imageio.ImageIO;
import javax.swing.*;

public class Trader extends Entity {

    public BufferedImage Logo;
    public String imageFileName;
    public String nickName;
    public String name;
    public int place;
    public int capital=50000;
    public int coins=500;
    private static final Font defaultFont = new JLabel().getFont();
    public int a=10;

    public Trader(String imageFileName,String name,String nickName,int place){
        this.nickName=nickName;
        this.imageFileName=imageFileName;
        this.place=place;
        this.name=name;

        try {
            Logo = ImageIO.read(new File(imageFileName));
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public Order createOrder() {

        Common common=Common.getInstance();


        Random randomNumberGenerator = new Random();
        int sellorbuy = randomNumberGenerator.nextInt(2);
        int size = randomNumberGenerator.nextInt(4) +1;






        if(sellorbuy == 0) {
            Order order=common.sellOrderFactory.createOrder(this,size);
            order.position=new Position(place*(common.windowWidth/common.numOfTraders) ,4 *(common.windowHeight/8) -18);
            return order;
        }
        else {
            Order order=common.buyOrderFactory.createOrder(this,size);
            order.position=new Position(place*(common.windowWidth/common.numOfTraders) ,4 *(common.windowHeight/8) -18);
            return order;
        }
    }

    public void draw(Graphics2D g2d) {

        Common common=Common.getInstance();



        int upperLeftX=place*(common.windowWidth/common.numOfTraders);
        int upperLeftY=4 *(common.windowHeight/8);
        int width=common.windowWidth/common.numOfTraders;
        int height=(5*common.windowHeight/12);

        g2d.setPaint(Color.BLACK);
        g2d.drawRect(upperLeftX, upperLeftY, width, height);

        g2d.drawImage(Logo,upperLeftX + width/30,upperLeftY,29*(width/30),3*(height/5),null);


        Font myFont = new Font ("Courier New", 1, 17);
        g2d.setFont (myFont);
        drawStringMiddleOfPanel(name,g2d,upperLeftX,upperLeftY+ (12*(height/20)),width,1*(height/20));

        g2d.setPaint(Color.magenta);
        drawStringMiddleOfPanel("'"+nickName+"'",g2d,upperLeftX,upperLeftY+ (13*(height/20)),width,1*(height/20));



        int fortune=( (common.windowHeight / 5) - 4 -common.plot.prices.get(common.plot.prices.size()-1) )*coins + capital;

        myFont=new Font ("TimesRoman", 1, 17);
        g2d.setFont (myFont);
        g2d.setPaint(Color.BLUE);
        drawStringMiddleOfPanel(coins + " coins",g2d,upperLeftX,upperLeftY+ (14*(height/20)),width,1*(height/20));

        myFont = new Font ("Courier New", 1, 17);
        g2d.setFont (myFont);
        g2d.setPaint(Color.GREEN);
        drawStringMiddleOfPanel(capital+" cash",g2d,upperLeftX,upperLeftY+ (15*(height/20)),width,1*(height/20));

        myFont = new Font ("TimesRoman", 1, 17);
        g2d.setFont (myFont);
        g2d.setPaint(Color.BLACK);
        drawStringMiddleOfPanel("Net: "+ fortune,g2d,upperLeftX,upperLeftY+ (16*(height/20)),width,1*(height/20));
        //g2d.drawString("'"+nickName+"'",(upperLeftX + width/30), upperLeftY + (4*(height/5)));

    }

    @Override
    public void step(){
        //Common.getInstance().orders.add(createOrder() );
        if (a--== 0){
            Common.getInstance().orders.add(createOrder() );
            //System.out.println("üretti");
            a=10;
        }
        //fortune-=1;

    }

    private void drawStringMiddleOfPanel(String string, Graphics2D g2d,int x,int y,int width,int height) {
        String message2 = string;
        int stringWidth = 0;
        int stringAccent = 0;
        int xCoordinate = 0;
        int yCoordinate = 0;
        // get the FontMetrics for the current font
        FontMetrics fm = g2d.getFontMetrics();


        /** display new message */
        /** Centering the text */
        // find the center location to display
        stringWidth = fm.stringWidth(message2);
        stringAccent = fm.getAscent();
        // get the position of the leftmost character in the baseline
        xCoordinate = width / 2 - stringWidth / 2;
        yCoordinate = height / 2 + stringAccent / 2;

        xCoordinate+=x;
        yCoordinate+=y;

        // draw String
        g2d.drawString(message2, xCoordinate, yCoordinate);
    }


}