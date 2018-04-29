import java.util.Random;

public class Shake extends State {

    public Shake() {
    }

    @Override
    public void step(ConMan conman){

        getToken(conman);

        if(--conman.timeToChange==0){

            conman.x=-25;
            conman.y=-25;

            Random rand=new Random();
            int randomNumber=rand.nextInt(3);
            if (randomNumber==0){
                conman.state=new ChaseClosest();
            }
            else if(randomNumber==1){
                conman.state=new GotoXY();
                Common common=Common.getInstance();
                double x=rand.nextInt( common.windowWidth -30) + 30;
                double y=rand.nextInt((3 * common.windowHeight) / 10 ) + common.windowHeight/5 ;
                //System.out.print(conman.name+" directionı "+x+" "+y);
                conman.direction=new Position(x,y);

            }
            else if(randomNumber==2){
                conman.state=new Rest();
            }

            conman.timeToChange=50;
        }else{

            //shake it up sekerim
            if(conman.shakeDirection==1){
                conman.x+=10;
                conman.shakeDirection=0;
            }else{
                conman.x-=10;
                conman.shakeDirection=1;
            }

        }

    }
}