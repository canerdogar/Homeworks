import java.util.ArrayList;
import java.util.List;

public abstract class State {

    public State() {
    }

    public abstract void step(ConMan conman);

    public void getToken(ConMan conman){

        List<Integer> indices =new ArrayList<>();
        Common common=Common.getInstance();
        for (int i=0;i< common.orders.size();i++){

            double distance = common.orders.get(i).position.distanceTo(conman.position);

            if ( distance < 25){
                //System.out.println("Yakaladim");
                indices.add(i);
            }

        }

        for (int i=indices.size()-1;i>=0 ;i--){

            int price=common.plot.prices.get(common.plot.prices.size()-1);

            int orderSize=common.orders.get(indices.get(i).intValue()).size;

            if(common.orders.get(indices.get(i).intValue()).getClass().getName().equals("BuyOrder") ){

                common.orders.get(indices.get(i).intValue()).trader.capital -= price*orderSize;


            }else if (common.orders.get(indices.get(i).intValue()).getClass().getName().equals("SellOrder")){

                common.orders.get(indices.get(i).intValue()).trader.coins -= orderSize;

            }

            conman.fortune += price*orderSize;

            common.orders.remove(indices.get(i).intValue());

        }


    }


}