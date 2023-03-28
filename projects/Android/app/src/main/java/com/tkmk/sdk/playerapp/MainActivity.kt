package com.tkmk.sdk.playerapp

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
import com.tkmk.sdk.playerapp.ui.theme.Tango_playerTheme

data class Video(val name: String, val url: String)

val TAG = "MainActivity"


val videos_4k = listOf(
    Video("H264 8M,RESOLUTION=3840x2160",
        ""),
    Video("H265 8M,RESOLUTION=3840x2160",
        ""),
)

val videos_h264_1080p = listOf(
    Video("H264 10M,RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-dd09517d68cba0709ab9e3370e92721e-video-sd.m3u8"),
    Video("H264 8M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-96f734bc345954ab9eecca74c795828d-video-sd.m3u8"),
    Video("H264 7M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-67af5fe334f33f4bf7c9390e47609c3a-video-sd.m3u8"),
    Video("H264 6M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-45f1d49dd76eca41c584f0d3b742d47b-video-sd.m3u8"),
    Video("H264 5M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-9ed5e37c6ec476bc5a7fbe22d82b89b8-video-sd.m3u8"),
    Video("H264 4M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-df68ae0b610393b764a5acbfe3d718bc-video-sd.m3u8"),
)

val videos_h265_1080p = listOf(
    Video("H265 10M,RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-9fdd7afa9fa816325ede21c5cbc6dcb4-video-sd.m3u8"),
    Video("H265 8M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-b81c90e91c6baae1c515ef9ea5dc0b52-video-sd.m3u8"),
    Video("H265 7M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-36c207b7bc5dcfc0a6aabf44147f51f1-video-sd.m3u8"),
    Video("H265 6M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-b94d7c819e48465d85450eff8806fb51-video-sd.m3u8"),
    Video("H265 5M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-a183654daf290691e6b6f5eb6fd440b5-video-sd.m3u8"),
    Video("H265 4M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-557dbc97a6ba6378c47b0bedd78cef11-video-sd.m3u8"),
)

val videos_h264_1440p = listOf(
    Video("H264 10M,RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-7a554e60fe47a5997039202a267719b3-video-sd.m3u8"),
    Video("H264 8M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-ba5974fc056839d3f3dbe839e557eefd-video-sd.m3u8"),
    Video("H264 7M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-c2be234aea3ec8daac9a4abec4d54cba-video-sd.m3u8"),
    Video("H264 6M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-8835cc5586ef91e6cc7bad1bbc4fbde0-video-sd.m3u8"),
    Video("H264 5M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-e7a66801fcde99473b747e1b05d2e0c4-video-sd.m3u8"),
    Video("H264 4M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-29d4121e1f39b536519f865b2466ffe2-video-sd.m3u8"),
)

val videos_h265_1440p = listOf(
    Video("H265 10M,RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-751b7cc1e063900c7b76ab0e757c6ffb-video-sd.m3u8"),
    Video("H265 8M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-a8e6585d4d253b15bcbd9481ff5a6732-video-sd.m3u8"),
    Video("H265 7M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-8968582822145a08f58b421602fd905d-video-sd.m3u8"),
    Video("H265 6M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-5a4a9f0466e3e99857cbb49d09d69c7e-video-sd.m3u8"),
    Video("H265 5M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-2a644d1ff9fa9a7fbc26137d1f6b3fb8-video-sd.m3u8"),
    Video("H265 4M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-2b762fa6602a5764725d8fd02789d054-video-sd.m3u8"),
)

val videos = listOf(

    //seek test , seek to  29437
    Video("seek test",""),
    Video("Single 1",
        "https://vod.tango.cn/b74010f1e6664dd8ab70c9c09f040fdf/cebb32490d354a1497d42167acb63482.m3u8"),
    Video("Multiple 1",
    "https://vod.tango.cn/50208f608fe471ed80386732a78f0102/fcad0a1d0060446cac161a470c60c221.m3u8"),

    //4K-8M test
    Video("4K-8M",""),
    Video("H264 8M,RESOLUTION=3840x2160",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b926919b97ab43689d61fe64c8e5ddb1-0a59692fd3896480c00692787d9cc547-video-sd.m3u8"),
    Video("H265 8M,RESOLUTION=3840x2160",
        "https://"),


    //h264-1080p-4m-10m-test.mp4
    Video("H264-1080p",""),
    Video("H264 10M,RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-dd09517d68cba0709ab9e3370e92721e-video-sd.m3u8"),
    Video("H264 8M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-96f734bc345954ab9eecca74c795828d-video-sd.m3u8"),
    Video("H264 7M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-67af5fe334f33f4bf7c9390e47609c3a-video-sd.m3u8"),
    Video("H264 6M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-45f1d49dd76eca41c584f0d3b742d47b-video-sd.m3u8"),
    Video("H264 5M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-9ed5e37c6ec476bc5a7fbe22d82b89b8-video-sd.m3u8"),
    Video("H264 4M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/81ec3270811571ed80af6732b78e0102/video/b55ebb143a5f4ee08b9ee9441aa74672-df68ae0b610393b764a5acbfe3d718bc-video-sd.m3u8"),

    //h265-1080p-4m-10m-test.mp4
    Video("H265-1080p",""),
    Video("H265 10M,RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-9fdd7afa9fa816325ede21c5cbc6dcb4-video-sd.m3u8"),
    Video("H265 8M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-b81c90e91c6baae1c515ef9ea5dc0b52-video-sd.m3u8"),
    Video("H265 7M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-36c207b7bc5dcfc0a6aabf44147f51f1-video-sd.m3u8"),
    Video("H265 6M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-b94d7c819e48465d85450eff8806fb51-video-sd.m3u8"),
    Video("H265 5M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-a183654daf290691e6b6f5eb6fd440b5-video-sd.m3u8"),
    Video("H265 4M, RESOLUTION=1920x1080",
        "https://vod.tango.cn/3cdcc41081dd71ed80bc6732b78e0102/video/f831b6a8c3df4516bd3c6ab7ee49fbfd-557dbc97a6ba6378c47b0bedd78cef11-video-sd.m3u8"),

    //h264-1440p-4m-10m-test.mp4
    Video("H264-1440p",""),
    Video("H264 10M,RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-7a554e60fe47a5997039202a267719b3-video-sd.m3u8"),
    Video("H264 8M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-ba5974fc056839d3f3dbe839e557eefd-video-sd.m3u8"),
    Video("H264 7M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-c2be234aea3ec8daac9a4abec4d54cba-video-sd.m3u8"),
    Video("H264 6M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-8835cc5586ef91e6cc7bad1bbc4fbde0-video-sd.m3u8"),
    Video("H264 5M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-e7a66801fcde99473b747e1b05d2e0c4-video-sd.m3u8"),
    Video("H264 4M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/81ed1cd0811571ed80470675b3ed0102/video/24f29664d06b45ce8949ea587c833dbc-29d4121e1f39b536519f865b2466ffe2-video-sd.m3u8"),

    //h265-1440p-4m-10m-test.mp4
    Video("H265-1440p",""),
    Video("H265 10M,RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-751b7cc1e063900c7b76ab0e757c6ffb-video-sd.m3u8"),
    Video("H265 8M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-a8e6585d4d253b15bcbd9481ff5a6732-video-sd.m3u8"),
    Video("H265 7M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-8968582822145a08f58b421602fd905d-video-sd.m3u8"),
    Video("H265 6M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-5a4a9f0466e3e99857cbb49d09d69c7e-video-sd.m3u8"),
    Video("H265 5M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-2a644d1ff9fa9a7fbc26137d1f6b3fb8-video-sd.m3u8"),
    Video("H265 4M, RESOLUTION=2560x1440",
        "https://vod.tango.cn/3cd019e081dd71edb52a6732b68e0102/video/531eb5d1e15d4666be65959a172bc6dd-2b762fa6602a5764725d8fd02789d054-video-sd.m3u8"),

    )

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        val read_permission = Manifest.permission.READ_EXTERNAL_STORAGE
        val write_permission =  Manifest.permission.WRITE_EXTERNAL_STORAGE
        val checkSelfPermission = ActivityCompat.checkSelfPermission(baseContext, write_permission)

        if (checkSelfPermission  == PackageManager.PERMISSION_GRANTED) {

        }else{
            var permissions = arrayOf(read_permission, write_permission)
            requestPermissions(permissions,1)
        }

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
        ListVideosSplit(collect = "videos_4k", videos = videos_4k)
        ListVideosSplit(collect = "h264-1080p", videos = videos_h264_1080p)
        ListVideosSplit(collect = "h265-1080p", videos = videos_h265_1080p)
        ListVideosSplit(collect = "h264-1440p", videos = videos_h264_1440p)
        ListVideosSplit(collect = "h265-1440p", videos = videos_h265_1440p)
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
