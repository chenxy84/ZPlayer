package vip.someone.sdk.playerapp

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.app.ActivityCompat
import vip.someone.sdk.playerapp.ui.theme.Tango_playerTheme

data class Video(val name: String, val url: String)

val TAG = "MainActivity"

val videos = listOf(
    Video("Local test",""),
    Video("","/sdcard/Samples/test1.mp4"),
    Video("","/sdcard/Samples/test1.webm"),
    Video("","/sdcard/Samples/test_dolby_vision.mp4"),
    Video("", "/sdcard/Samples/4035d397-17db85911c1.mov"),
    Video("", "/sdcard/Samples/179d548b-17b9a44c6eb.mp4")
)

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        val read_permission = Manifest.permission.READ_MEDIA_VIDEO
        val write_permission =  Manifest.permission.WRITE_EXTERNAL_STORAGE

        do {
            var checkSelfPermission =
                ActivityCompat.checkSelfPermission(baseContext, read_permission)

            if (checkSelfPermission  == PackageManager.PERMISSION_GRANTED) {

            }else{
                var permissions = arrayOf(read_permission, read_permission)
                requestPermissions(permissions,1)
            }

            checkSelfPermission =
                ActivityCompat.checkSelfPermission(baseContext, write_permission)

            if (checkSelfPermission  == PackageManager.PERMISSION_GRANTED) {

            }else{
                var permissions = arrayOf(read_permission, write_permission)
                requestPermissions(permissions,1)
            }

        } while(false)


        super.onCreate(savedInstanceState)
        setContent {
            Tango_playerTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    //modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    //VideoPage()
                    ListVideos(videos)

                }
            }
        }

    }
}

@Composable
fun VideoPage() {
    Column {
//        ListVideosSplit(collect = "videos_4k", videos = videos_4k)
//        ListVideosSplit(collect = "h264-1080p", videos = videos_h264_1080p)
//        ListVideosSplit(collect = "h265-1080p", videos = videos_h265_1080p)
//        ListVideosSplit(collect = "h264-1440p", videos = videos_h264_1440p)
//        ListVideosSplit(collect = "h265-1440p", videos = videos_h265_1440p)

    }

}

@Composable
fun ListVideos(videos: List<Video>) {
    val context = LocalContext.current
    Column() {
        LazyColumn {
            items(videos.size) { index ->
                if(videos[index].url.isEmpty()) {
                    Text(videos[index].name, modifier = Modifier.padding(4.dp, 4.dp, 4.dp, 4.dp), fontSize = 30.sp)
                } else {
                    Column(modifier = Modifier.clickable {
                        Log.d(TAG, "play url: " + videos[index].name)
                        var intent = Intent(context, VideoActivity::class.java)
                        intent.putExtra("name", videos[index].name)
                        intent.putExtra("url", videos[index].url)
                        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        context.startActivity(intent)

                    }) {

                        Text(videos[index].name, modifier = Modifier.padding(4.dp, 4.dp, 4.dp, 2.dp), fontSize = 18.sp)
                        Text(videos[index].url, modifier = Modifier.padding(4.dp, 2.dp, 4.dp, 4.dp), fontSize = 14.sp)

                    }
                }

                Divider()
            }
        }
    }
}

@Composable
fun ListVideosSplit(collect: String, videos: List<Video>) {
    val context = LocalContext.current
    Column() {
        Text(collect, modifier = Modifier.padding(4.dp, 4.dp, 4.dp, 4.dp), fontSize = 30.sp)
        videos.forEach { video ->
            Column(modifier = Modifier.clickable {
                Log.d(TAG, "play url: " + video.name)
                var intent = Intent(context, VideoActivity::class.java)
                intent.putExtra("name", video.name)
                intent.putExtra("url", video.url)
                context.startActivity(intent)
            }) {
                Text(video.name, modifier = Modifier.padding(4.dp, 4.dp, 4.dp, 2.dp), fontSize = 18.sp)
                Text(video.url, modifier = Modifier.padding(4.dp, 2.dp, 4.dp, 4.dp), fontSize = 14.sp)
                Divider()
            }
        }
    }
}
