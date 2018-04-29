import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Logger;

import weka.associations.GeneralizedSequentialPatterns;
import weka.core.Instances;

public class Hw2Q4 {

	private static final Logger logger = Logger.getLogger("DataSet");

	public static void main(String[] args) {

		float minSups[] = { 0.3f, 0.5f, 0.7f };
		if (args.length != 1) {
			logger.severe("You should give the path of the dataset!");
			return;
		}
		Instances data;
		try {
			data = readData(args[0]);

			for (float minSup : minSups) {
				logger.info(String.format("\nRunning GSP with minimum support %f:\n==========\n", minSup));

				long time = System.currentTimeMillis();

				GeneralizedSequentialPatterns result = getResult(data, minSup);

				time = System.currentTimeMillis() - time;

				logger.info(String.format("Running GSP took %d ms.", time));
				logger.info(result.toString());
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Reads data in arff format and returns instances.
	 * 
	 * @param path
	 *            of the arff file
	 * @return Instances object.
	 * @throws IOException
	 */
	public static Instances readData(String path) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(path));
 		Instances data = new Instances(reader);
 		reader.close();
		return data;
	}

	/**
	 * Build association from the given data with GeneralizedSequentialPatterns.
	 * @param data 
	 * @param minSup minimum support of the pattern
	 * @return Built GSP
	 * @throws Exception
	 */
	public static GeneralizedSequentialPatterns getResult(Instances data, float minSup) throws Exception {
		GeneralizedSequentialPatterns gsp = new GeneralizedSequentialPatterns();
		gsp.setMinSupport(minSup);
		gsp.buildAssociations(data);
		return gsp;
	}
}
