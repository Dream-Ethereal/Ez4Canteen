<template>
  <div>
	  <view class="page-title-container">
	  	<text class="page-title">README文档</text>
	  </view>
    
    <!-- 根据模式显示内容 -->
	<div v-html="renderedMarkdown" class="markdown-body"></div>
  </div>
</template>

<script>
  import axios from 'axios';
  import { marked } from 'marked';
  import hljs from 'highlight.js'; // 从 npm 中直接引入 highlight.js
  import 'highlight.js/styles/github.css'; // 引入代码高亮样式

  // 配置 marked 库
  marked.setOptions({
    highlight: function(code, lang) {
      if (hljs.getLanguage(lang)) {
        return hljs.highlight(code, { language: lang }).value;
      } else {
        return hljs.highlightAuto(code).value;
      }
    },
    breaks: true,  // 支持 GFM 换行符
    gfm: true,     // 支持 GitHub 风格的 Markdown 语法
    tables: true,  // 启用表格支持
  });

  export default {
    data() {
      return {
        markdownContent: '' // Markdown内容将从外部文件中加载
      };
    },
    computed: {
      // 使用 marked 将 Markdown 内容转化为 HTML
      renderedMarkdown() {
        return marked(this.markdownContent);
      }
    },
    methods: {
      // 加载 Markdown 文件
      async loadMarkdownFile() {
        try {
          const response = await axios.get('https://mp-13a86627-9a4d-45d3-a214-e84c157a7c27.cdn.bspapp.com/web-about/LOG.md');
          this.markdownContent = response.data;
        } catch (error) {
          console.error('无法加载Markdown文件:', error);
        }
      }
    },
    created() {
      // 组件创建时加载 Markdown 文件
      this.loadMarkdownFile();
    }
  };
</script>

<style>
.page-title-container {
		display: flex;
		flex-direction: column;
		align-items: center; /* Center horizontally */
		margin-bottom: 20px; /* Space below the title */
	}

.page-title {
	margin-top: 20px;
	font-size: 36px; /* Increased font size for the page title */
	font-weight: bold;
	text-align: center; /* Ensure the text is centered within its container */
	position: relative; /* Needed for the pseudo-element positioning */
}

.page-title::after {
	content: ""; /* Required to display the border */
	display: block;
	width: 50%; /* Width of the line */
	height: 2px; /* Thickness of the line */
	background-color: #ccc; /* Color of the line */
	position: absolute;
	bottom: -10px; /* Position below the title with some space */
	left: 50%;
	transform: translateX(-50%); /* Center the line horizontally */
}
	
/* GitHub 风格的 Markdown 样式 */
.markdown-body {
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji";
  line-height: 1.6;
  padding: 20px;
  border: 1px solid #e1e4e8;
  border-radius: 6px;
  background-color: #ffffff;
  color: #24292e;
  overflow-x: auto;
}

.markdown-body h1, .markdown-body h2, .markdown-body h3 {
  border-bottom: 1px solid #eaecef;
  padding-bottom: 0.3em;
}

.markdown-body pre {
  background-color: #f6f8fa;
  padding: 16px;
  overflow: auto;
  border-radius: 6px;
}

/* 表格样式 */
.markdown-body table {
  border-collapse: collapse;
  margin: 20px 0;
  width: 100%;
}

.markdown-body table th,
.markdown-body table td {
  padding: 8px;
  border: 1px solid #dfe2e5;
}

.markdown-body table th {
  background-color: #f6f8fa;
  font-weight: bold;
}

/* 可根据需要调整样式 */
</style>
