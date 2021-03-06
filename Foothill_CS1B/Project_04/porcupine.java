package zooanimals;

public class porcupine implements iAnimal, Comparable<iAnimal> {

    private String animalType = "Porcupine";
    private int IdTag;
    private int MAX_TEMP = 80;
    private int MIN_TEMP = 55;

    @Override
    public String getAnimalType() {
        return animalType;
    }

    @Override
    public void setIdTag(int anIdTag) {
        IdTag = anIdTag;
    }

    @Override
    public int getIdTag() {
        return IdTag;
    }

    @Override
    public int getMaxTemperature() {
        return MAX_TEMP;
    }

    @Override
    public int getMinTemperature() {
        return MIN_TEMP;
    }

    @Override
    public int compareTo(iAnimal other) {
        if (this.getIdTag() == other.getIdTag() && this.getAnimalType().equals(other.getAnimalType())) {
            return 1;
        }
        return 0;
    }
}
