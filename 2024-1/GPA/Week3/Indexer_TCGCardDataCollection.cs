public class TCGCardDataCollection {
    /// <summary>
    /// 카드 종류
    /// </summary>
    public enum CardKind {
        NORMAL  = 100_000,
        SPECIAL = 200_000,
        ACE     = 300_000,
        LEGEND  = 400_000
    }

    /// <param name="kind">인덱스를 알아낼 CardKind 키</param>
    public int this[CardKind kind] => Array.IndexOf(Enum.GetNames(typeof(CardKind)), Enum.GetName(kind));
}
