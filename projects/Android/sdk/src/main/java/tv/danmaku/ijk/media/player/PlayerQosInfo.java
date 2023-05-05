package tv.danmaku.ijk.media.player;

public class PlayerQosInfo {

    public float vfps;
    public float vdps;
    public int width;
    public int height;
    public long bitrate;

    public long videoCachedDuration;
    public long videoCachedBytes;
    public long videoCachedPackets;

    public long tcpSpeed;
    public long startPlayTime;
    public long firstScreenTime;
    public long endPlayTime;

    public long estimateBandwidth;
    public long videoDecodeFailedCount;
    public long videoRefreshBlockCount;

    @Override
    public String toString() {
        return "PlayerQosInfo{" +
                "vfps=" + vfps +
                ", vdps=" + vdps +
                ", width=" + width +
                ", height=" + height +
                ", bitrate=" + bitrate +
                ", videoCachedDuration=" + videoCachedDuration +
                ", videoCachedBytes=" + videoCachedBytes +
                ", videoCachedPackets=" + videoCachedPackets +
                ", tcpSpeed=" + tcpSpeed +
                ", startPlayTime=" + startPlayTime +
                ", firstScreenTime=" + firstScreenTime +
                ", endPlayTime=" + endPlayTime +
                ", estimateBandwidth=" + estimateBandwidth +
                ", videoDecodeFailedCount=" + videoDecodeFailedCount +
                ", videoRefreshBlockCount=" + videoRefreshBlockCount +
                '}';
    }
}
