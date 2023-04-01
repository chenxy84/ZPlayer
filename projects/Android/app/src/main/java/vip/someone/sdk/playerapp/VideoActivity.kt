package vip.someone.sdk.playerapp

import android.os.Bundle
import android.util.Log
import android.view.Window
import android.view.WindowManager
import android.widget.ImageView
import android.widget.RelativeLayout
import android.widget.SeekBar
import android.widget.SeekBar.OnSeekBarChangeListener
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.contains
import com.aliyun.player.IPlayer
import com.aliyun.player.bean.InfoCode
import com.aliyun.player.source.UrlSource
import vip.someone.sdk.playerapp.util.HardwareInfoUtils
import tv.danmaku.ijk.media.player.IMediaPlayer
import tv.danmaku.ijk.media.player.IMediaPlayer.OnPreparedListener
import tv.danmaku.ijk.media.player.widget.*
import kotlinx.coroutines.runBlocking
import java.io.BufferedOutputStream
import java.io.FileOutputStream
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter

class VideoActivity : AppCompatActivity() {

    val TAG = "VideoActivity"
    val infoUtil = HardwareInfoUtils()

    val useAliSDK = false
    var playerView: AbstractPlayerView? = null

    var name: String? = null
    var url: String? = null

    var isPlayerStarted = false

    lateinit var playerHolder: RelativeLayout
    lateinit var aliyunView: AliyunRenderView
    lateinit var ijkView: IjkVideoView

    lateinit var timeSeekBar: SeekBar
    lateinit var timeStartText: TextView
    lateinit var closeBtn: ImageView

    var threadDebugInfo: Thread? = null
    var isDebugInfoRunning = false
    lateinit var textDebugInfo: TextView

    var totalDuration = 0L

    fun toTimeStr(msec: Long) : String {
        var total_sec = msec / 1000
        var hour = total_sec / 3600
        //var minute = (total_sec - hour * 3600) / 60
        var minute = (total_sec % 3600) / 60
        //var sec = total_sec - hour * 3600 - minute * 60
        var sec = total_sec % 60
        return String.format("%02d:%02d:%02d", hour, minute, sec)
    }

    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        hideActionStatusBar()
        setContentView(R.layout.activity_video)

        //set screen on
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)

        name =  intent.getStringExtra("name")
        url = intent.getStringExtra("url")

        aliyunView = AliyunRenderView(baseContext)
        ijkView = IjkVideoView(baseContext)

        playerHolder = findViewById(R.id.player_view_holder)
        playerHolder.setOnClickListener {
            if(isPlayerStarted) {
                playerView?.pause()
                isPlayerStarted = false
            } else {
                playerView?.start()
                isPlayerStarted = true
            }

        }

        timeSeekBar = findViewById(R.id.time_seekbar)
        timeSeekBar.max = 100000
        timeStartText = findViewById(R.id.time_start)

        timeSeekBar.setOnSeekBarChangeListener(object : OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                //Log.d(TAG, "progress = ${progress}")
                var time = totalDuration * progress.div(100000.0)
                this@VideoActivity.runOnUiThread(Runnable {
                    timeStartText.text = toTimeStr(time.toLong())
                })
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {
                Log.d(TAG, "onStartTrackingTouch")
            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {
                val progress = seekBar!!.progress
                Log.d(TAG, "onStopTrackingTouch ${progress}")
                var seekTo = totalDuration * progress.div(100000.0)
                playerView?.seekTo(seekTo.toLong())
            }
        })

        textDebugInfo = findViewById(R.id.debug_info_text)
        closeBtn = findViewById(R.id.close_btn)

        closeBtn.setOnClickListener {
            this@VideoActivity.finish()
        }

    }

    private fun hideActionStatusBar() {
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN)
        supportActionBar?.hide()
        actionBar?.hide()
    }

    override fun finish() {
        window.clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        playerView?.stop()
        playerView?.release()

        super.finish()
    }

    override fun onStart() {
        Log.d(TAG, "onStart")
        super.onStart()

        if(!isPlayerStarted) {
            startPlayer()
            isPlayerStarted = true
        }
        if (threadDebugInfo == null) {
            threadDebugInfo = Thread(Runnable {
                isDebugInfoRunning = true
                var update_time = System.currentTimeMillis()
                val formatted_data = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy_MM_dd_HH_mm_ss"))
                val writer = BufferedOutputStream(FileOutputStream("/sdcard/Download/player_log_${formatted_data}.txt"))

                while(isDebugInfoRunning) {

                    val now = System.currentTimeMillis()
                    if((now - update_time)  > 1000) {
                        var qosInfo = playerView?.qosInfo

                        if (qosInfo != null) {
                            runBlocking {
                                var cpu = infoUtil.getCPUUsage()
                                var mem = infoUtil.getAppOccupyMemory(baseContext)
                                var log_detail = "${qosInfo.width}, ${qosInfo.height}, ${qosInfo.vfps}, ${qosInfo.vdps}, ${qosInfo.tcpSpeed}, ${cpu}, ${mem}"
                                writer.write("${log_detail}\n".toByteArray())
                                writer.flush()

                                this@VideoActivity.runOnUiThread {
                                    var bitrate = String.format("%.2f", qosInfo.bitrate / (1024 * 1024.0))
                                    var tcp_speed = String.format("%.2f", qosInfo.tcpSpeed / (1024 * 1024.0))
                                    var text =
                                        "width:  ${qosInfo.width}\n" +
                                                "height:  ${qosInfo.height}\n" +
                                                "vfps: ${qosInfo.vfps}\n" +
                                                "vdps: ${qosInfo.vdps}\n" +
                                                "bitrate: $bitrate (Mbps)\n" +
                                                "tcp_speed: $tcp_speed (Mbps)\n" +
                                                "cpu: ${cpu}\n" +
                                                "mem: ${mem}"

                                    textDebugInfo.text = text
                                }
                                Log.d(TAG, "qos: ${log_detail}")
                            }
                            update_time = now
                        }
                    }
                    Thread.sleep(200)
                }
            })
            threadDebugInfo?.start()
        }

    }

    override fun onStop() {
        Log.d(TAG, "onStop")
        super.onStop()
        if(isPlayerStarted) {
            isPlayerStarted = false
            stopPlayer()
        }

        if(threadDebugInfo != null) {
            isDebugInfoRunning = false
            threadDebugInfo?.join()
            threadDebugInfo = null
        }
    }

    //    var startX: Float = 0f
//    override fun onTouchEvent(event: MotionEvent?): Boolean {
//        Log.i(TAG,"onTouch")
//
//        when(event?.action) {
//            MotionEvent.ACTION_DOWN -> {
//                startX = event.x
//                Log.i(TAG, "onTouch start x = $startX")
//            }
//            MotionEvent.ACTION_UP -> {
//                val distance = event.x - startX
//                val position = playerView?.currentPosition
//
//                Log.i(TAG,"onTouch end x = $distance, position = $position, seek to")
//            }
//
//        }
//
//        return super.onTouchEvent(event)
//    }


    fun updateSeekBarProgress(pos: Long) {
        var progressVal = pos.div(totalDuration * 1.0) * 100000
        //Log.d(TAG, "progressVal ${progressVal}")
        this@VideoActivity.runOnUiThread(Runnable {
            timeSeekBar.progress = progressVal.toInt()
        })
    }

    fun startPlayer() {

        val urlSource = UrlSource()
        urlSource.uri = url


        val playerConfig = aliyunView.playerConfig
        // 更换渲染模式
        playerConfig.mEnableVideoTunnelRender = true
        //播放器设置网路超时时间为 15000x`ms
        playerConfig.mNetworkTimeout = 17000
        // 设置超时重试次数
        playerConfig.mNetworkRetryCount = 3
        // 配置起播缓冲区时长s
        playerConfig.mStartBufferDuration = 1500
        // 配置最大缓冲区时长s
        playerConfig.mMaxBufferDuration = 50000
        aliyunView.playerConfig = playerConfig

        aliyunView.setOnPreparedListener(IPlayer.OnPreparedListener {
            //Log.d(TAG, "totalDuration: ${aliyunView.aliPlayer.duration}" )
            totalDuration = aliyunView.aliPlayer.duration
        })

        aliyunView.setOnInfoListener(IPlayer.OnInfoListener {
            when(it.code) {
                InfoCode.CurrentPosition -> {
                    //Log.d(TAG, "CurrentPosition: ${it.extraValue}" )
                    updateSeekBarProgress(it.extraValue)
                }
                else -> {

                }
            }
        })

        ijkView.setOnPreparedListener(OnPreparedListener {
            //Log.d(TAG, "totalDuration: ${ijkView.duration}" )
            totalDuration = ijkView.duration
        })

        ijkView.setOnInfoListener(IMediaPlayer.OnInfoListener { _, what, extra ->
            when(what) {
//                IMediaPlayer.MEDIA_INFO_MEDIA_CURRENT_POSITION -> {
//                    Log.d(TAG, "SEEK_TEST CurrentPosition: $extra" )
//                    updateSeekBarProgress(extra.toLong())
//                }
            }
            true
         })

        ijkView.setOnSeekCompleteListener {
            Log.d(TAG, "SEEK_TEST setOnSeekCompleteListener")

        }


        if(useAliSDK) {
            playerView = aliyunView
        } else {
            playerView = ijkView
        }

        playerHolder.addView(playerView,
            RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT))

        //        playerHolder.addView(playerView, 2160, 1215)

        playerView?.setSurfaceType(AliyunRenderView.SurfaceType.TEXTURE_VIEW)
        playerView?.setDataSource(urlSource)

        playerView?.setAutoPlay(true)
        playerView?.setLoop(true)
        playerView?.prepare()


//        val progressBar = ProgressBar(baseContext, null,     Attr.ProgetprogressBarStyleHorizontal)
//        progressBar.min = 0
//        progressBar.max = 100
//        progressBar.progress = 50
//        progressBar.
//        playerView?.addView(progressBar)


        Log.d(TAG, "playerView prepare url $url")
    }

    fun stopPlayer() {
        playerView?.stop()
        playerView?.release()

        playerHolder.removeAllViews()
    }
}