public class TempRecord {
    // 값 목록
    private float[] temps = new float[10] {
        56.2F, 56.7F, 56.5F, 56.9F,
        58.8F, 61.3F, 65.9F, 62.1F,
        59.2F, 57.5F
    };
    
    /// <summary>
    /// 값의 개수
    /// </summary>
    public int Length => temps.Length;
    
    /// <param name="index">값 인덱스</param>
    public float this[int index] {
        get => temps[index];
        set => temps[index] = value;
    }
}
