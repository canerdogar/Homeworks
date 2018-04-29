import com.sun.prism.paint.Color;

import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.geom.AffineTransform;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


public class Ticker extends Entity {


    public Ticker(){

        int height=Common.getInstance().windowHeight;
        int x=0;
        positions=new ArrayList<>();
        status=new ArrayList<>();
        Random rand=new Random();
        for(int i=0;i<100;i++){
            status.add(rand.nextInt(3));
            positions.add(new Position(x,height-60));
            x+=80;
        }


    }

    // [...]
    private void drawArrowHead(Graphics2D g2d,String companyName,Position position,int i) {

        AffineTransform tx = new AffineTransform();
        //Line2D.Double line = new Line2D.Double(100,1000,200,200);

        Polygon arrowHead = new Polygon();
        arrowHead.addPoint( 70,0);
        arrowHead.addPoint( 65, -10);
        arrowHead.addPoint( 75,-10);

        //tx.setToIdentity();
        //double angle = Math.atan2(line.y2-line.y1, line.x2-line.x1);
        tx.translate(position.getX(),position.getY());
        g2d.setColor(java.awt.Color.BLACK);
        //tx.rotate((angle-Math.PI/2d));
        g2d.drawString(companyName,0,0);
        //Graphics2D g = (Graphics2D) g2d.create();
        g2d.setTransform(tx);
        if(status.get(i)==0){
            //tx.rotate(20);
            g2d.setColor(java.awt.Color.BLACK);
        }else if(status.get(i)==1){
            //tx.rotate(45);
            g2d.setColor(java.awt.Color.RED);
        }else{
            g2d.setColor(java.awt.Color.GREEN);
        }

        g2d.fill(arrowHead);
        //g2d.dispose();
    }

    private final String [] bist100 = { "AEFES" , "AFYON" , "AKBNK" , "AKENR" , "AKSA"  , "AKSEN" , "ALARK" , "ALCTL" , "ALGYO" , "ALKIM" ,
            "ANACM" , "ANELE" , "ARCLK" , "ASELS" , "AYGAZ" , "BAGFS" , "BANVT" , "BIMAS" , "BIZIM" , "BJKAS" ,
            "BRISA" , "CCOLA" , "CEMTS" , "CLEBI" , "CRFSA" , "DEVA"  , "DOAS"  , "DOHOL" , "ECILC" , "EGEEN" ,
            "EKGYO" , "ENKAI" , "ERBOS" , "EREGL" , "FENER" , "FROTO" , "GARAN" , "GLYHO" , "GOLTS" , "GOODY" ,
            "GOZDE" , "GSDHO" , "GSRAY" , "GUBRF" , "HALKB" , "HLGYO" , "ICBCT" , "IHLAS" , "IPEKE" , "ISCTR" ,
            "ISGYO" , "IZMDC" , "KARSN" , "KARTN" , "KCHOL" , "KIPA"  , "KLGYO" , "KONYA" , "KORDS" , "KOZAA" ,
            "KOZAL" , "KRDMD" , "MAVI"  , "METRO" , "MGROS" , "NETAS" , "NTTUR" , "ODAS"  , "OTKAR" , "PETKM" ,
            "PGSUS" , "PRKME" , "SAHOL" , "SASA"  , "SISE"  , "SKBNK" , "SODA"  , "TATGD" , "TAVHL" , "TCELL" ,
            "THYAO" , "TKFEN" , "TKNSA" , "TMSN"  , "TOASO" , "TRCAS" , "TRKCM" , "TSKB"  , "TSPOR" , "TTKOM" ,
            "TTRAK" , "TUPRS" , "ULKER" , "VAKBN" , "VESTL" , "VKGYO" , "YATAS" , "YAZIC" , "YKBNK" , "ZOREN" } ;

    //-------------------------------------------------------------------------------------------------------------------------------------------------

    public List<Position> positions;

    public List<Integer> status;

    @Override
    public  void step(){

        for(int i=0;i<positions.size();i++){

            Position pos=positions.get(i);
            pos.x-=1;
            if(pos.x == -7200){

                pos.x=800;

            }
            //positions.set(i,)

        }

    }

    @Override
    public  void draw(Graphics2D g2d){

        g2d.setColor(java.awt.Color.GRAY);
        g2d.fillRect(0,Common.getInstance().windowHeight-60,Common.getInstance().windowWidth,30);

        for(int i=0;i<bist100.length;i++){

            //System.out.println(bist100[i]+" being printed in "+positions.get(i).getX()+" "+positions.get(i).getY());
            drawArrowHead(g2d,bist100[i],positions.get(i),i);

        }

    }
}
