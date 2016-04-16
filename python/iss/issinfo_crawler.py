#!/usr/bin/env python
#-*-coding:utf-8-*-

from send_notify import send_notify
from send_email import send_email

import urllib
import urllib2
import re
import sqlite3

def read_iss_bachelor_page(page):
    global info_pagesize
    global url_iss_bachelor_info
    global iss_bachelor_info_type

    values_iss = {}
    values_iss["infoType"] = iss_bachelor_info_type
    values_iss["pageNumber"] = page
    values_iss["pageSize"] = info_pagesize
    values_iss["contentDiv"] = "mdl1"
    values_iss["navigateDiv"] = "tnt_pagination1"
    values_iss["tableWidth"] = "255"
    values_iss["order"] = "1"

    values_iss = urllib.urlencode(values_iss)

    url_iss_bachelor_info += "?" + values_iss

    request = urllib2.Request(url_iss_bachelor_info)
    iss_bachelor_info = urllib2.urlopen(request).read()
    return iss_bachelor_info

def get_iss_bachelor_info(page):
    global conn
    global cursor
    global iss_message
    global new_message_from_iss_bachelor_info
    global info_pagesize
    global email_to
    iss_bachelor_info = read_iss_bachelor_page(page)
    base_bachelor_info_url = "http://www.iss.whu.edu.cn/one/bachelor/generalContent.template"
    pattern = re.compile(r'title="(?P<title>.*)" href="[a-z_]*\.html\?nid=(?P<nid>[0-9]*)"')
    for m in re.finditer(pattern, iss_bachelor_info):
        title = m.group('title').decode('utf-8')
        url = base_bachelor_info_url + "?nid=" + m.group('nid')
        try:
            cursor.execute("INSERT INTO iss_bachelor_info VALUES(?, ?)", (title, url))
        except sqlite3.IntegrityError:
            return None
        else:
            iss_message[title] = url
            new_message_from_iss_bachelor_info += 1
            page_html = urllib2.urlopen(url).read()
            download_urls = re.findall('<a href="/.*"', page_html)
            if download_urls != None:
                for i in download_urls:
                    i_replace = i.replace("\"/", "\"http://www.iss.whu.edu.cn/")
                    #re.sub(i, download_url, page_html)
                    page_html = page_html.replace(i, i_replace)
            send_email(email_to, title, page_html, "html")
    conn.commit()
    if new_message_from_iss_bachelor_info == page * info_pagesize:
        get_iss_bachelor_info(page + 1)

def read_teachersblog_info(page):
    global info_pagesize
    global url_teachersblog_info
    global teacher_name
    global class_name

    values_teacher = {}
    values_teacher["author"] = teacher_name
    values_teacher["pageNumber"] = page
    values_teacher["pageSize"] = info_pagesize
    values_teacher["type"] = class_name

    values_teacher = urllib.urlencode(values_teacher)

    url_teachersblog_info += "?" + values_teacher

    request = urllib2.Request(url_teachersblog_info)
    iss_teacherblog_info = urllib2.urlopen(request).read()
    return iss_teacherblog_info
    
def get_teachersblog_info(page):
    global conn
    global cursor
    global chengang_message
    global new_message_from_chengang
    global new_homework_from_chengang
    global info_pagesize
    global email_to
    iss_teacherblog_info = read_teachersblog_info(page)
    base_teacherblog_info_url = "http://www.iss.whu.edu.cn/one/blog/blogcontent.template"
    pattern = re.compile(r'<h3><a href="javascript:showBlogContent\(\'(?P<bid>[0-9]*)\'\,\'(?P<author>.*)\'\);">(?P<title>.*)</a></h3>')
    for m in re.finditer(pattern, iss_teacherblog_info):
        title = m.group('title').decode('utf-8')
        url = base_teacherblog_info_url + "?" + "bid=" + m.group('bid') + "$^@^$author=" + m.group('author')
        try:
            cursor.execute("INSERT INTO iss_teacherblogs_info VALUES(?, ?, ?)", (title, url, m.group('author')))
        except sqlite3.IntegrityError:
            return None
        else:
            chengang_message[title] = url
            new_message_from_chengang += 1
            send_email(email_to, title, urllib2.urlopen(url).read(), "html")
            if title.find(u'作业') != -1:
                new_homework_from_chengang += 1
        conn.commit()
    if new_message_from_chengang == page * info_pagesize:
        get_teachersblog_info(page + 1)

def print_iss_msg():
    global new_message_from_iss_bachelor_info
    
    if new_message_from_iss_bachelor_info != 0:
        message = str(new_message_from_iss_bachelor_info) + "条来自国际软件学院的新消息\n"
        send_notify(message)

def print_teachersblog_msg():
    global new_message_from_chengang
    global new_homework_from_chengang
    
    if new_message_from_chengang != 0:
        message =  str(new_message_from_chengang) + "条来自陈刚的新消息"
        if new_homework_from_chengang != 0:
            message += "，其中有" + str(new_homework_from_chengang) + "个新作业\n"
        else:
            message += "\n"
        send_notify(message)

## CONFIG
start_page = 1
info_pagesize = 16
url_iss_bachelor_info = "http://www.iss.whu.edu.cn/one/bachelor/bachelorContent.template"
iss_bachelor_info_type =  u"本科教学_教学通知".encode("utf-8")
url_teachersblog_info = "http://www.iss.whu.edu.cn/one/blog/blog.template"
teacher_name =  "chengang"
class_name =  u"UNIX程序设计".encode("utf-8")

email_to = ["inksmallfrog@gmail.com", "523587181@qq.com"]
    
## process
new_message_from_iss_bachelor_info = 0
iss_message={}
new_message_from_chengang = 0
chengang_message={}
new_homework_from_chengang = 0

conn = sqlite3.connect('/home/inksmallfrog/sqlite/iss_info.db')
cursor = conn.cursor()
cursor.execute("CREATE TABLE IF NOT EXISTS iss_bachelor_info(title TEXT PRIMARY KEY NOT NULL, url TEXT)")
cursor.execute("CREATE TABLE IF NOT EXISTS iss_teacherblogs_info(title TEXT PRIMARY KEY NOT NULL, url TEXT, author TEXT)")

get_iss_bachelor_info(start_page)
get_teachersblog_info(start_page)

print_iss_msg()
print_teachersblog_msg()

