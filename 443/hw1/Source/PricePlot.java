//import java.awt.*;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.*;
import java.util.List;

public class PricePlot extends Entity {

    public BufferedImage Logo;
    public String imageFileName="Hitcoin.gif";

    public List<Integer> prices;

    public PricePlot(){



        prices=new ArrayList<Integer>();
        prices.add(randomPrice());
        for (int i=0;i<7 * (Common.getInstance().windowWidth/8) -1;i++){

            prices.add(randomPrice( prices.get(prices.size()-1) ));
        }

    }

    private int randomPrice ()
    {
        Common common=Common.getInstance();

        int value = generateRandomInt( 1 , common.windowHeight / 5 ) ;

        return value ;
    }

    //=================================================================================================================================================

    private int randomPrice ( int previousPrice )
    {
        Common common=Common.getInstance();

        int value = previousPrice + generateRandomInt( 0 , 30 ) - 15 ;

        if ( value <= 0                 )  { value = 1                     ; }
        if ( value >= common.windowHeight / 5 )  { value = (common.windowHeight / 5) - 4 ; }

        return value ;
    }

    @Override
    public  void step(){

        prices.remove(0);
        prices.add( randomPrice( prices.get(prices.size()-1) ) );
        List<Integer> indices =new ArrayList<>();
        Common common=Common.getInstance();
        for (int i=0;i< common.orders.size();i++){

            if (common.orders.get(i).position.getY() <= (common.orders.get(i).destination.getY()) ){
                indices.add(i);
            }

        }

        for (int i=indices.size()-1;i>=0 ;i--){

            if(common.orders.get(indices.get(i).intValue()).getClass().getName().equals("BuyOrder") ){

                common.orders.get(indices.get(i).intValue()).trader.capital -= common.orders.get(indices.get(i).intValue()).size * prices.get(prices.size()-1);


                common.orders.get(indices.get(i).intValue()).trader.coins += common.orders.get(indices.get(i).intValue()).size;

            }else if (common.orders.get(indices.get(i).intValue()).getClass().getName().equals("SellOrder")){

                common.orders.get(indices.get(i).intValue()).trader.capital += common.orders.get(indices.get(i).intValue()).size * prices.get(prices.size()-1);


                common.orders.get(indices.get(i).intValue()).trader.coins -= common.orders.get(indices.get(i).intValue()).size;
                //System.out.println("sellorder");

            }

            common.orders.remove(indices.get(i).intValue());

        }

    }

    @Override
    public  void draw(Graphics2D g2d){

        Common common=Common.getInstance();
        try {
            this.Logo = ImageIO.read(new File(imageFileName));
        }catch(Exception e){

            e.printStackTrace();

        }



        g2d.drawImage(Logo,0,0,common.windowWidth/8,common.windowHeight/5,null);

        g2d.setPaint(Color.BLACK);
        //g2d.drawRect(common.windowWidth/8, 0, 7 * (common.windowWidth/8), common.windowHeight/5);

        int y=common.windowHeight/50;
        for (int i=0;i<10;i++){

            g2d.drawLine(common.windowWidth/8,y,common.windowWidth,y);
            y+=common.windowHeight/50;

        }

        int x=common.windowWidth/8 + 1;
        for (int i=0;i<50;i++){

            g2d.drawLine(x,0,x,common.windowHeight/5);
            x+=common.windowWidth/40;

        }

        g2d.setPaint(Color.GREEN);
        int x1=(common.windowWidth/8) + 1;
        for (int i=0;i<prices.size()-1;i++){

            g2d.drawLine(x1,prices.get(i),x1+1,prices.get(i+1));
            x1+=1;
        }

    }

    public int generateRandomInt(int min,int max){
        Random rand=new Random();
        return rand.nextInt((max-min) +1) + min;
    }


    public Position generateRandomDirection(){
        Random rand=new Random();
        int x = rand.nextInt(7 * (Common.getInstance().windowWidth/8) -1);

        x+=(Common.getInstance().windowWidth/8);

        return new Position(x,Common.getInstance().windowHeight / 5);
    }

}
