const SAVE_HTML_KEY = "KatexHTMLOutput";
const SAVE_MD_KEY = "MarkdownInput";

const updateRender = async () => {
  const htmlDiv = document.getElementById("html-output");
  renderMathInElement(htmlDiv, {
    delimiters: [
      {left: "$$", right: "$$", display: true},
      {left: "$", right: "$", display: false}
    ],
    throwError: false,
  });
}

const download = async (filename, mime, text) => {
  let ele = document.createElement("a");
  ele.setAttribute("href", "data:" + mime + ";charset=utf-8," + encodeURIComponent(text));
  ele.setAttribute("download", filename);
  ele.style.display = 'none';
  document.body.appendChild(ele);
  ele.click();
  document.body.removeChild(ele);
};

const downloadMd = async () => {
  const md = document.getElementById("markdown-input");
  download("markdown.md", "text/plain", md.value);
};

const getRequiredCss = async () => {
  let css = "";
  const css1 = document.getElementById("main-stylesheet").sheet;
  const css2 = document.getElementById("math-stylesheet").sheet;
  css += Array.from(css1.cssRules).map(rule => rule.cssText).join(' ');
  css += Array.from(css2.cssRules).map(rule => rule.cssText).join(' ');
  return css
};

const downloadHTML = async () => {
  const css = await getRequiredCss();
  const htmlEle = document.getElementById("html-output");
  let html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><style>"
  html += css;
  html += "</style></head><body>";
  html += htmlEle.innerHTML;
  html += "</body></html>";
  download("output.html", "text/html", html);
};

const setStatus = async (msg) => {
  const statusBox = document.getElementById("status");
  statusBox.innerText = msg;
};

const saveHTML = async () => {
  setStatus("Saving HTML...");
  const html = document.getElementById("html-output");
  localStorage.setItem(SAVE_HTML_KEY, html.innerHTML);
  setStatus("Saved");
};

const saveMd = async () => {
  setStatus("Saving markdown...");
  const md = document.getElementById("markdown-input");
  localStorage.setItem(SAVE_MD_KEY, md.value);
  setStatus("Saved");
};

const renderHTML = async () => {
  setStatus("Rendering...");
  const md = new remarkable.Remarkable({
    html: true,
  });
  const markdownInput = document.getElementById("markdown-input");
  const htmlOutput = document.getElementById("html-output");
  const newHtml = md.render(markdownInput.value);
  htmlOutput.innerHTML = newHtml;
  updateRender();
  saveMd();
  saveHTML();
  setStatus("Done");
}

document.addEventListener("DOMContentLoaded", async () => {
  console.log("loaded");

  // preload save
  if (localStorage.getItem(SAVE_HTML_KEY) !== null){
    const html = document.getElementById("html-output");
    html.innerHTML = localStorage.getItem(SAVE_HTML_KEY);
  }
  if (localStorage.getItem(SAVE_MD_KEY) !== null){
    const md = document.getElementById("markdown-input");
    md.value = localStorage.getItem(SAVE_MD_KEY);
  }

  const updateBtn = document.getElementById("update-html");
  updateBtn.addEventListener("click", renderHTML);

  const saveMdBtn = document.getElementById("save-markdown");
  saveMdBtn.addEventListener("click", saveMd);

  const saveHTMLBtn = document.getElementById("save-html");
  saveHTMLBtn.addEventListener("click", saveHTML);

  const downloadMdBtn = document.getElementById("download-markdown");
  downloadMdBtn.addEventListener("click", downloadMd);
  const downloadHTMLBtn = document.getElementById("download-html");
  downloadHTMLBtn.addEventListener("click", downloadHTML);
});
