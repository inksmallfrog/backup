#!/usr/bin/env python
#-*-coding:utf-8-*-

from send_email import send_email
from send_notify import send_notify

import urllib
import urllib2
import re

import sqlite3

def clear_html(html):
    retHtml = html.replace('\n', '')
    retHtml = retHtml.replace('\r', '')
    retHtml = retHtml.replace('&nbsp;', '')
    retHtml = retHtml.replace(' ', '')
    return retHtml

def get_new_movies_info():
    global meicao_movie_base_url
    global meicao_movies_info_url

    global conn
    global cursor

    meicao_info_html = urllib2.urlopen(meicao_movies_info_url).read().decode('gb2312').encode('utf-8')
    regex = re.compile(u'<td width="87%" class="k2"><a href="(?P<url>.*)" class=.*>(?P<title>.*)</a></td>'.encode('utf-8'))
    for m in re.finditer(regex, meicao_info_html):
        title = m.group('title')
        url = meicao_movie_base_url + m.group('url')
        movie_html = urllib2.urlopen(url).read().decode('gb2312').encode('utf-8')
        movie_html = clear_html(movie_html)
        match_result = re.search(u'<P>电影名称：</P><P>(?P<name>.*)</P><P>时间：(?P<time>.*)</P><P>地点'.encode('utf-8'), movie_html)
        if match_result == None:
            time = ''
            try:
                cursor.execute("INSERT INTO meicao_movie VALUES(?, ?)", (title, "None"))
            except sqlite3.IntegrityError:
                return None
            else:
                message = title
                #print message
                send_email(email_to, "梅操电影消息", message, "plain")
                send_notify(message)
        else:
            name_str = match_result.group('name')
            name_str = name_str.replace('<P>', '')
            name_str = name_str.replace('</P>', ' ')
            time = match_result.group('time')
            try:
                cursor.execute("INSERT INTO meicao_movie VALUES(?, ?)", (title, time))
            except sqlite3.IntegrityError:
                return None
            else:
                message = time + ': ' + name_str
                #print message
                send_email(email_to, "梅操电影 " + time, message, "plain")
                send_notify(message)

    conn.commit()

###CONFIG
email_to = ["inksmallfrog@gmail.com", "523587181@qq.com"]
meicao_movie_base_url = "http://vhost.whu.edu.cn/gh/"
meicao_movies_info_url = "http://vhost.whu.edu.cn/gh/xywh.php?Class_Type=0&Class_ID=42"

###DATABASE
conn = sqlite3.connect("/home/inksmallfrog/sqlite/meicao_movie_info.db")
conn.text_factory = str
cursor = conn.cursor()
cursor.execute("CREATE TABLE IF NOT EXISTS meicao_movie(title TEXT PRIMARY KEY NOT NULL, time TEXT)")

get_new_movies_info()
