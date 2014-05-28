




<!DOCTYPE html>
<html class="   ">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    
    
    <title>DestructibleBox2D/src/main.cpp at master · seemk/DestructibleBox2D · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <meta property="fb:app_id" content="1401488693436528"/>

      <meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="seemk/DestructibleBox2D" name="twitter:title" /><meta content="Contribute to DestructibleBox2D development by creating an account on GitHub." name="twitter:description" /><meta content="https://avatars0.githubusercontent.com/u/5329631?s=400" name="twitter:image:src" />
<meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="https://avatars0.githubusercontent.com/u/5329631?s=400" property="og:image" /><meta content="seemk/DestructibleBox2D" property="og:title" /><meta content="https://github.com/seemk/DestructibleBox2D" property="og:url" /><meta content="Contribute to DestructibleBox2D development by creating an account on GitHub." property="og:description" />

    <link rel="assets" href="https://assets-cdn.github.com/">
    <link rel="conduit-xhr" href="https://ghconduit.com:25035/">
    <link rel="xhr-socket" href="/_sockets" />

    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
      <meta name="google-analytics" content="UA-3769691-2">

    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="C82A00FD:7CF4:61AA1F0:5386152E" name="octolytics-dimension-request_id" />
    

    
    
    <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico" />


    <meta content="authenticity_token" name="csrf-param" />
<meta content="5Pfsuu0AhG+JUuDHPAInaIs/qisKE9pPhK92X9wg5N52Pe2TyP4M9JWbTCSMW/yP0ANyK+sWEv0Pm7wb5ObAoQ==" name="csrf-token" />

    <link href="https://assets-cdn.github.com/assets/github-1121bb0260c396426f82723a30b276d949f537a3.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://assets-cdn.github.com/assets/github2-712fa8c0954e275d6626ee28d9660e79c77e47c6.css" media="all" rel="stylesheet" type="text/css" />
    


    <meta http-equiv="x-pjax-version" content="3f16474b6e3a1ed04126225242cc563e">

      
  <meta name="description" content="Contribute to DestructibleBox2D development by creating an account on GitHub." />

  <meta content="5329631" name="octolytics-dimension-user_id" /><meta content="seemk" name="octolytics-dimension-user_login" /><meta content="18764265" name="octolytics-dimension-repository_id" /><meta content="seemk/DestructibleBox2D" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="18764265" name="octolytics-dimension-repository_network_root_id" /><meta content="seemk/DestructibleBox2D" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/seemk/DestructibleBox2D/commits/master.atom" rel="alternate" title="Recent Commits to DestructibleBox2D:master" type="application/atom+xml" />

  </head>


  <body class="logged_out  env-production windows vis-public page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>
    <div class="wrapper">
      
      
      
      


      
      <div class="header header-logged-out">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/">
      <span class="mega-octicon octicon-logo-github"></span>
    </a>

    <div class="header-actions">
        <a class="button primary" href="/join">Sign up</a>
      <a class="button signin" href="/login?return_to=%2Fseemk%2FDestructibleBox2D%2Fblob%2Fmaster%2Fsrc%2Fmain.cpp">Sign in</a>
    </div>

    <div class="command-bar js-command-bar  in-repository">

      <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
        <li class="features"><a href="/features">Features</a></li>
          <li class="enterprise"><a href="https://enterprise.github.com/">Enterprise</a></li>
          <li class="blog"><a href="/blog">Blog</a></li>
      </ul>
        <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<div class="commandbar">
  <span class="message"></span>
  <input type="text" data-hotkey="s, /" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    
      data-repo="seemk/DestructibleBox2D"
      data-branch="master"
      data-sha="572c1089751b3977f12d7a602674bf09dea32f2c"
  >
  <div class="display hidden"></div>
</div>

    <input type="hidden" name="nwo" value="seemk/DestructibleBox2D" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target" role="button" aria-haspopup="true">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container" aria-hidden="true">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="help tooltipped tooltipped-s" aria-label="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
    </div>

  </div>
</div>



      <div id="start-of-content" class="accessibility-aid"></div>
          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    <div id="js-flash-container">
      
    </div>
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">


  <li>
    <a href="/login?return_to=%2Fseemk%2FDestructibleBox2D"
    class="minibutton with-count star-button tooltipped tooltipped-n"
    aria-label="You must be signed in to star a repository" rel="nofollow">
    <span class="octicon octicon-star"></span>Star
  </a>

    <a class="social-count js-social-count" href="/seemk/DestructibleBox2D/stargazers">
      0
    </a>

  </li>

    <li>
      <a href="/login?return_to=%2Fseemk%2FDestructibleBox2D"
        class="minibutton with-count js-toggler-target fork-button tooltipped tooltipped-n"
        aria-label="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-repo-forked"></span>Fork
      </a>
      <a href="/seemk/DestructibleBox2D/network" class="social-count">
        0
      </a>
    </li>
</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author"><a href="/seemk" class="url fn" itemprop="url" rel="author"><span itemprop="title">seemk</span></a></span><!--
       --><span class="path-divider">/</span><!--
       --><strong><a href="/seemk/DestructibleBox2D" class="js-current-repository js-repo-home-link">DestructibleBox2D</a></strong>

          <span class="page-context-loader">
            <img alt="" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      <div class="repository-with-sidebar repo-container new-discussion-timeline js-new-discussion-timeline  ">
        <div class="repository-sidebar clearfix">
            

<div class="sunken-menu vertical-right repo-nav js-repo-nav js-repository-container-pjax js-octicon-loaders">
  <div class="sunken-menu-contents">
    <ul class="sunken-menu-group">
      <li class="tooltipped tooltipped-w" aria-label="Code">
        <a href="/seemk/DestructibleBox2D" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-hotkey="g c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /seemk/DestructibleBox2D">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped tooltipped-w" aria-label="Issues">
          <a href="/seemk/DestructibleBox2D/issues" aria-label="Issues" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g i" data-selected-links="repo_issues /seemk/DestructibleBox2D/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>0</span>
            <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped tooltipped-w" aria-label="Pull Requests">
        <a href="/seemk/DestructibleBox2D/pulls" aria-label="Pull Requests" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g p" data-selected-links="repo_pulls /seemk/DestructibleBox2D/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


    </ul>
    <div class="sunken-menu-separator"></div>
    <ul class="sunken-menu-group">

      <li class="tooltipped tooltipped-w" aria-label="Pulse">
        <a href="/seemk/DestructibleBox2D/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="pulse /seemk/DestructibleBox2D/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Graphs">
        <a href="/seemk/DestructibleBox2D/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_graphs repo_contributors /seemk/DestructibleBox2D/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Network">
        <a href="/seemk/DestructibleBox2D/network" aria-label="Network" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-selected-links="repo_network /seemk/DestructibleBox2D/network">
          <span class="octicon octicon-repo-forked"></span> <span class="full-word">Network</span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

              <div class="only-with-full-nav">
                

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/seemk/DestructibleBox2D.git" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/seemk/DestructibleBox2D.git" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/seemk/DestructibleBox2D" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/seemk/DestructibleBox2D" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <span class="help tooltipped tooltipped-n" aria-label="Get help on which URL is right for you.">
    <a href="https://help.github.com/articles/which-remote-url-should-i-use">
    <span class="octicon octicon-question"></span>
    </a>
  </span>
</p>


  <a href="http://windows.github.com" class="minibutton sidebar-button" title="Save seemk/DestructibleBox2D to your computer and use it in GitHub Desktop." aria-label="Save seemk/DestructibleBox2D to your computer and use it in GitHub Desktop.">
    <span class="octicon octicon-device-desktop"></span>
    Clone in Desktop
  </a>

                <a href="/seemk/DestructibleBox2D/archive/master.zip"
                   class="minibutton sidebar-button"
                   aria-label="Download seemk/DestructibleBox2D as a zip file"
                   title="Download seemk/DestructibleBox2D as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
              </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<a href="/seemk/DestructibleBox2D/blob/15b48d851d3901ee3ab214cfcb6ba2fdb44de99d/src/main.cpp" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:fece04c8af130ad7b463b2d03fbbc024 -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/seemk/DestructibleBox2D/find/master" data-pjax data-hotkey="t" class="js-show-file-finder" style="display:none">Show File Finder</a>

<div class="file-navigation">
  

<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="master"
    data-ref="master"
    role="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-x js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/seemk/DestructibleBox2D/blob/master/src/main.cpp"
                 data-name="master"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/seemk/DestructibleBox2D" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">DestructibleBox2D</span></a></span></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/seemk/DestructibleBox2D/tree/master/src" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">src</span></a></span><span class="separator"> / </span><strong class="final-path">main.cpp</strong> <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="src/main.cpp" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
  </div>
</div>


  <div class="commit file-history-tease">
      <img alt="seemk" class="main-avatar js-avatar" data-user="5329631" height="24" src="https://avatars3.githubusercontent.com/u/5329631?s=140" width="24" />
      <span class="author"><a href="/seemk" rel="author">seemk</a></span>
      <time datetime="2014-04-15T20:28:17+03:00" is="relative-time" title-format="%Y-%m-%d %H:%M:%S %z" title="2014-04-15 20:28:17 +0300">April 15, 2014</time>
      <div class="commit-title">
          <a href="/seemk/DestructibleBox2D/commit/04ced37b70eff1c992b599263970a9b85be5abdb" class="message" data-pjax="true" title="Added optional simplify, antialiasing.">Added optional simplify, antialiasing.</a>
      </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>1</strong>  contributor</a></p>
      
    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list">
          <li class="facebox-user-list-item">
            <img alt="seemk" class=" js-avatar" data-user="5329631" height="24" src="https://avatars3.githubusercontent.com/u/5329631?s=140" width="24" />
            <a href="/seemk">seemk</a>
          </li>
      </ul>
    </div>
  </div>

<div class="file-box">
  <div class="file">
    <div class="meta clearfix">
      <div class="info file-name">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
        <span class="meta-divider"></span>
          <span>314 lines (262 sloc)</span>
          <span class="meta-divider"></span>
        <span>8.985 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
            <a class="minibutton tooltipped tooltipped-w"
               href="http://windows.github.com" aria-label="Open this file in GitHub for Windows">
                <span class="octicon octicon-device-desktop"></span> Open
            </a>
              <a class="minibutton disabled tooltipped tooltipped-w" href="#"
                 aria-label="You must be signed in to make or propose changes">Edit</a>
          <a href="/seemk/DestructibleBox2D/raw/master/src/main.cpp" class="button minibutton " id="raw-url">Raw</a>
            <a href="/seemk/DestructibleBox2D/blame/master/src/main.cpp" class="button minibutton js-update-url-with-hash">Blame</a>
          <a href="/seemk/DestructibleBox2D/commits/master/src/main.cpp" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
          <a class="minibutton danger disabled empty-icon tooltipped tooltipped-w" href="#"
             aria-label="You must be signed in to make or propose changes">
          Delete
        </a>
      </div><!-- /.actions -->
    </div>
      
  <div class="blob-wrapper data type-c js-blob-data">
       <table class="file-code file-diff tab-size-8">
         <tr class="file-code-line">
           <td class="blob-line-nums">
             <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>

           </td>
           <td class="blob-line-code"><div class="code-body highlight"><pre><div class='line' id='LC1'><span class="cp">#include &lt;SFML/Graphics.hpp&gt;</span></div><div class='line' id='LC2'><span class="cp">#include &lt;memory&gt;</span></div><div class='line' id='LC3'><span class="cp">#include &lt;Box2D/Box2D.h&gt;</span></div><div class='line' id='LC4'><span class="cp">#include &quot;DebugDraw.h&quot;</span></div><div class='line' id='LC5'><span class="cp">#include &quot;ShapeFactory.h&quot;</span></div><div class='line' id='LC6'><span class="cp">#include &quot;Geometry.h&quot;</span></div><div class='line' id='LC7'><span class="cp">#include &quot;Constants.h&quot;</span></div><div class='line' id='LC8'><span class="cp">#include &lt;unordered_set&gt;</span></div><div class='line' id='LC9'><span class="cp">#include &lt;iostream&gt;</span></div><div class='line' id='LC10'><br/></div><div class='line' id='LC11'><span class="k">namespace</span> <span class="n">bg</span> <span class="o">=</span> <span class="n">boost</span><span class="o">::</span><span class="n">geometry</span><span class="p">;</span></div><div class='line' id='LC12'><br/></div><div class='line' id='LC13'><span class="k">typedef</span> <span class="n">std</span><span class="o">::</span><span class="n">unordered_set</span><span class="o">&lt;</span><span class="n">b2Body</span><span class="o">*&gt;</span> <span class="n">QueryResult</span><span class="p">;</span></div><div class='line' id='LC14'><span class="k">typedef</span> <span class="n">std</span><span class="o">::</span><span class="n">pair</span><span class="o">&lt;</span><span class="n">b2Body</span><span class="o">*</span><span class="p">,</span> <span class="kt">ring_t</span><span class="o">&gt;</span> <span class="kt">match_t</span><span class="p">;</span></div><div class='line' id='LC15'><br/></div><div class='line' id='LC16'><span class="k">struct</span> <span class="n">Shape</span></div><div class='line' id='LC17'><span class="p">{</span></div><div class='line' id='LC18'>	<span class="k">enum</span> <span class="n">Category</span></div><div class='line' id='LC19'>	<span class="p">{</span></div><div class='line' id='LC20'>		<span class="n">normal</span>	     <span class="o">=</span> <span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="mi">0</span><span class="p">),</span></div><div class='line' id='LC21'>		<span class="n">destructible</span> <span class="o">=</span> <span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="mi">1</span><span class="p">)</span></div><div class='line' id='LC22'>	<span class="p">};</span></div><div class='line' id='LC23'><span class="p">};</span></div><div class='line' id='LC24'><br/></div><div class='line' id='LC25'><span class="k">namespace</span></div><div class='line' id='LC26'><span class="p">{</span></div><div class='line' id='LC27'>	<span class="k">const</span> <span class="kt">float</span> <span class="n">screenWidth</span> <span class="o">=</span> <span class="mf">1280.f</span><span class="p">;</span></div><div class='line' id='LC28'>	<span class="k">const</span> <span class="kt">float</span> <span class="n">screenHeight</span> <span class="o">=</span> <span class="mf">720.f</span><span class="p">;</span></div><div class='line' id='LC29'><span class="p">}</span></div><div class='line' id='LC30'><br/></div><div class='line' id='LC31'><span class="k">struct</span> <span class="n">WorldQueryCallback</span> <span class="o">:</span> <span class="k">public</span> <span class="n">b2QueryCallback</span></div><div class='line' id='LC32'><span class="p">{</span></div><div class='line' id='LC33'>	<span class="n">WorldQueryCallback</span><span class="p">(</span><span class="n">b2Shape</span><span class="o">::</span><span class="n">Type</span> <span class="n">filter</span><span class="p">,</span> <span class="n">Shape</span><span class="o">::</span><span class="n">Category</span> <span class="n">categoryFilter_</span><span class="p">)</span></div><div class='line' id='LC34'>	<span class="o">:</span> <span class="n">shapeFilter</span><span class="p">(</span><span class="n">filter</span><span class="p">)</span></div><div class='line' id='LC35'>	<span class="p">,</span> <span class="n">categoryFilter</span><span class="p">(</span><span class="n">categoryFilter_</span><span class="p">)</span></div><div class='line' id='LC36'>	<span class="p">{</span> <span class="p">}</span></div><div class='line' id='LC37'><br/></div><div class='line' id='LC38'>	<span class="kt">bool</span> <span class="n">ReportFixture</span><span class="p">(</span><span class="n">b2Fixture</span><span class="o">*</span> <span class="n">fixture</span><span class="p">)</span> <span class="n">override</span></div><div class='line' id='LC39'>	<span class="p">{</span></div><div class='line' id='LC40'>		<span class="k">auto</span> <span class="n">type</span> <span class="o">=</span> <span class="n">fixture</span><span class="o">-&gt;</span><span class="n">GetShape</span><span class="p">()</span><span class="o">-&gt;</span><span class="n">GetType</span><span class="p">();</span></div><div class='line' id='LC41'>		<span class="k">auto</span> <span class="n">fixtureCategory</span> <span class="o">=</span> <span class="n">fixture</span><span class="o">-&gt;</span><span class="n">GetFilterData</span><span class="p">().</span><span class="n">categoryBits</span><span class="p">;</span></div><div class='line' id='LC42'>		<span class="k">if</span> <span class="p">(</span><span class="n">type</span> <span class="o">==</span> <span class="n">shapeFilter</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">categoryFilter</span> <span class="o">&amp;</span> <span class="n">fixtureCategory</span><span class="p">))</span></div><div class='line' id='LC43'>		<span class="p">{</span></div><div class='line' id='LC44'>			<span class="n">foundBodies</span><span class="p">.</span><span class="n">insert</span><span class="p">(</span><span class="n">fixture</span><span class="o">-&gt;</span><span class="n">GetBody</span><span class="p">());</span></div><div class='line' id='LC45'>		<span class="p">}</span></div><div class='line' id='LC46'>		<span class="k">return</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC47'>	<span class="p">}</span></div><div class='line' id='LC48'><br/></div><div class='line' id='LC49'>	<span class="n">QueryResult</span> <span class="n">foundBodies</span><span class="p">;</span></div><div class='line' id='LC50'>	<span class="n">b2Shape</span><span class="o">::</span><span class="n">Type</span> <span class="n">shapeFilter</span><span class="p">;</span></div><div class='line' id='LC51'>	<span class="n">Shape</span><span class="o">::</span><span class="n">Category</span> <span class="n">categoryFilter</span><span class="p">;</span></div><div class='line' id='LC52'><br/></div><div class='line' id='LC53'><span class="p">};</span></div><div class='line' id='LC54'><br/></div><div class='line' id='LC55'><span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">&gt;&gt;</span> <span class="n">convertGeometry</span><span class="p">(</span><span class="k">const</span> <span class="kt">ring_collection_t</span><span class="o">&amp;</span> <span class="n">rings</span><span class="p">)</span></div><div class='line' id='LC56'><span class="p">{</span></div><div class='line' id='LC57'>	<span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">&gt;&gt;</span> <span class="n">shapes</span><span class="p">;</span></div><div class='line' id='LC58'>	<span class="k">for</span> <span class="p">(</span><span class="k">const</span> <span class="k">auto</span><span class="o">&amp;</span> <span class="n">r</span> <span class="o">:</span> <span class="n">rings</span><span class="p">)</span></div><div class='line' id='LC59'>	<span class="p">{</span></div><div class='line' id='LC60'>		<span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">&gt;</span> <span class="n">shape</span><span class="p">{</span> <span class="k">new</span> <span class="n">b2ChainShape</span><span class="p">()</span> <span class="p">};</span></div><div class='line' id='LC61'>		<span class="n">shape</span><span class="o">-&gt;</span><span class="n">CreateChain</span><span class="p">(</span><span class="n">r</span><span class="p">.</span><span class="n">data</span><span class="p">(),</span> <span class="n">r</span><span class="p">.</span><span class="n">size</span><span class="p">());</span></div><div class='line' id='LC62'>		<span class="n">shapes</span><span class="p">.</span><span class="n">push_back</span><span class="p">(</span><span class="n">std</span><span class="o">::</span><span class="n">move</span><span class="p">(</span><span class="n">shape</span><span class="p">));</span></div><div class='line' id='LC63'>	<span class="p">}</span></div><div class='line' id='LC64'><br/></div><div class='line' id='LC65'>	<span class="k">return</span> <span class="n">shapes</span><span class="p">;</span></div><div class='line' id='LC66'><span class="p">}</span></div><div class='line' id='LC67'><br/></div><div class='line' id='LC68'><span class="kt">void</span> <span class="n">step</span><span class="p">(</span><span class="n">b2World</span><span class="o">&amp;</span> <span class="n">world</span><span class="p">,</span> <span class="kt">float</span> <span class="n">dt</span><span class="p">)</span></div><div class='line' id='LC69'><span class="p">{</span></div><div class='line' id='LC70'>	<span class="k">const</span> <span class="kt">int</span> <span class="n">maxSteps</span> <span class="o">=</span> <span class="mi">20</span><span class="p">;</span></div><div class='line' id='LC71'>	<span class="k">const</span> <span class="kt">float</span> <span class="n">fixedDt</span> <span class="o">=</span> <span class="mf">1.0f</span> <span class="o">/</span> <span class="mf">60.f</span><span class="p">;</span></div><div class='line' id='LC72'>	<span class="k">const</span> <span class="kt">float</span> <span class="n">minDt</span> <span class="o">=</span> <span class="n">fixedDt</span> <span class="o">/</span> <span class="mf">10.f</span><span class="p">;</span></div><div class='line' id='LC73'>	<span class="kt">int</span> <span class="n">stepsPerformed</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC74'>	<span class="kt">float</span> <span class="n">frameTime</span> <span class="o">=</span> <span class="n">dt</span><span class="p">;</span></div><div class='line' id='LC75'><br/></div><div class='line' id='LC76'>	<span class="k">while</span> <span class="p">(</span><span class="n">frameTime</span> <span class="o">&gt;</span> <span class="mf">0.0f</span> <span class="o">&amp;&amp;</span> <span class="n">stepsPerformed</span> <span class="o">&lt;</span> <span class="n">maxSteps</span><span class="p">)</span></div><div class='line' id='LC77'>	<span class="p">{</span></div><div class='line' id='LC78'>		<span class="kt">float</span> <span class="n">delta</span> <span class="o">=</span> <span class="p">(</span><span class="n">std</span><span class="o">::</span><span class="n">min</span><span class="p">)(</span><span class="n">frameTime</span><span class="p">,</span> <span class="n">fixedDt</span><span class="p">);</span></div><div class='line' id='LC79'>		<span class="n">frameTime</span> <span class="o">-=</span> <span class="n">delta</span><span class="p">;</span></div><div class='line' id='LC80'>		<span class="k">if</span> <span class="p">(</span><span class="n">frameTime</span> <span class="o">&lt;</span> <span class="n">minDt</span><span class="p">)</span></div><div class='line' id='LC81'>		<span class="p">{</span></div><div class='line' id='LC82'>			<span class="n">delta</span> <span class="o">+=</span> <span class="n">frameTime</span><span class="p">;</span></div><div class='line' id='LC83'>			<span class="n">frameTime</span> <span class="o">=</span> <span class="mf">0.0f</span><span class="p">;</span></div><div class='line' id='LC84'>		<span class="p">}</span></div><div class='line' id='LC85'>		<span class="k">const</span> <span class="kt">int</span> <span class="n">velocityIterations</span> <span class="o">=</span> <span class="mi">8</span><span class="p">;</span></div><div class='line' id='LC86'>		<span class="k">const</span> <span class="kt">int</span> <span class="n">positionIterations</span> <span class="o">=</span> <span class="mi">3</span><span class="p">;</span></div><div class='line' id='LC87'>		<span class="n">world</span><span class="p">.</span><span class="n">Step</span><span class="p">(</span><span class="n">delta</span><span class="p">,</span> <span class="n">velocityIterations</span><span class="p">,</span> <span class="n">positionIterations</span><span class="p">);</span></div><div class='line' id='LC88'><br/></div><div class='line' id='LC89'>	<span class="p">}</span></div><div class='line' id='LC90'><br/></div><div class='line' id='LC91'>	<span class="n">world</span><span class="p">.</span><span class="n">ClearForces</span><span class="p">();</span></div><div class='line' id='LC92'><span class="p">}</span></div><div class='line' id='LC93'><br/></div><div class='line' id='LC94'><br/></div><div class='line' id='LC95'><br/></div><div class='line' id='LC96'><span class="kt">void</span> <span class="n">addStaticShapes</span><span class="p">(</span><span class="n">b2World</span><span class="o">&amp;</span> <span class="n">world</span><span class="p">)</span></div><div class='line' id='LC97'><span class="p">{</span></div><div class='line' id='LC98'><br/></div><div class='line' id='LC99'>	<span class="n">ShapeFactory</span> <span class="n">factory</span> <span class="p">{</span> <span class="n">constants</span><span class="o">::</span><span class="n">RENDER_SCALE</span> <span class="p">};</span></div><div class='line' id='LC100'>	<span class="c1">// Add the nondestructible screen edges</span></div><div class='line' id='LC101'>	<span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="n">b2Vec2</span><span class="o">&gt;</span> <span class="n">boundaryPoints</span> <span class="o">=</span></div><div class='line' id='LC102'>	<span class="p">{</span> <span class="n">b2Vec2</span><span class="p">{</span> <span class="mf">0.0f</span><span class="p">,</span> <span class="mf">0.0f</span> <span class="p">},</span> <span class="n">b2Vec2</span><span class="p">{</span> <span class="mf">0.0f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="p">},</span></div><div class='line' id='LC103'>	<span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="p">},</span> <span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span><span class="p">,</span> <span class="mf">0.0f</span> <span class="p">}</span> <span class="p">};</span></div><div class='line' id='LC104'>	<span class="k">auto</span> <span class="n">boundaryShape</span> <span class="o">=</span> <span class="n">factory</span><span class="p">.</span><span class="n">chain</span><span class="p">(</span><span class="n">boundaryPoints</span><span class="p">.</span><span class="n">data</span><span class="p">(),</span> <span class="n">boundaryPoints</span><span class="p">.</span><span class="n">size</span><span class="p">());</span></div><div class='line' id='LC105'><br/></div><div class='line' id='LC106'>	<span class="n">b2BodyDef</span> <span class="n">boundaryDef</span><span class="p">;</span></div><div class='line' id='LC107'>	<span class="n">b2Body</span><span class="o">*</span> <span class="n">boundaryBody</span> <span class="o">=</span> <span class="n">world</span><span class="p">.</span><span class="n">CreateBody</span><span class="p">(</span><span class="o">&amp;</span><span class="n">boundaryDef</span><span class="p">);</span></div><div class='line' id='LC108'>	<span class="k">auto</span> <span class="n">boundaryFixture</span> <span class="o">=</span> <span class="n">boundaryBody</span><span class="o">-&gt;</span><span class="n">CreateFixture</span><span class="p">(</span><span class="n">boundaryShape</span><span class="p">.</span><span class="n">get</span><span class="p">(),</span> <span class="mf">0.0f</span><span class="p">);</span></div><div class='line' id='LC109'>	<span class="k">auto</span> <span class="n">filter</span> <span class="o">=</span> <span class="n">boundaryFixture</span><span class="o">-&gt;</span><span class="n">GetFilterData</span><span class="p">();</span></div><div class='line' id='LC110'>	<span class="n">filter</span><span class="p">.</span><span class="n">categoryBits</span> <span class="o">=</span> <span class="n">Shape</span><span class="o">::</span><span class="n">normal</span><span class="p">;</span></div><div class='line' id='LC111'>	<span class="n">boundaryFixture</span><span class="o">-&gt;</span><span class="n">SetFilterData</span><span class="p">(</span><span class="n">filter</span><span class="p">);</span></div><div class='line' id='LC112'><br/></div><div class='line' id='LC113'>	<span class="c1">// Add a destructible polygon</span></div><div class='line' id='LC114'>	<span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="n">b2Vec2</span><span class="o">&gt;</span> <span class="n">polygonPoints</span> <span class="o">=</span></div><div class='line' id='LC115'>	<span class="p">{</span> <span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span> <span class="o">*</span> <span class="mf">0.1f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="o">*</span> <span class="mf">0.4f</span> <span class="p">},</span></div><div class='line' id='LC116'>	<span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span> <span class="o">*</span> <span class="mf">0.1f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="o">*</span> <span class="mf">0.95f</span> <span class="p">},</span></div><div class='line' id='LC117'>	<span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span> <span class="o">*</span> <span class="mf">0.9f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="o">*</span> <span class="mf">0.95f</span> <span class="p">},</span></div><div class='line' id='LC118'>	<span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span> <span class="o">*</span> <span class="mf">0.9f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="o">*</span> <span class="mf">0.7f</span> <span class="p">},</span></div><div class='line' id='LC119'>	<span class="n">b2Vec2</span><span class="p">{</span> <span class="n">screenWidth</span> <span class="o">*</span> <span class="mf">0.4f</span><span class="p">,</span> <span class="n">screenHeight</span> <span class="o">*</span> <span class="mf">0.4f</span> <span class="p">}</span> <span class="p">};</span></div><div class='line' id='LC120'><br/></div><div class='line' id='LC121'>	<span class="k">auto</span> <span class="n">polygonShape</span> <span class="o">=</span> <span class="n">factory</span><span class="p">.</span><span class="n">chain</span><span class="p">(</span><span class="n">polygonPoints</span><span class="p">.</span><span class="n">data</span><span class="p">(),</span> <span class="n">polygonPoints</span><span class="p">.</span><span class="n">size</span><span class="p">());</span></div><div class='line' id='LC122'>	<span class="n">b2BodyDef</span> <span class="n">polygonDef</span><span class="p">;</span></div><div class='line' id='LC123'>	<span class="n">b2Body</span><span class="o">*</span> <span class="n">polygonBody</span> <span class="o">=</span> <span class="n">world</span><span class="p">.</span><span class="n">CreateBody</span><span class="p">(</span><span class="o">&amp;</span><span class="n">polygonDef</span><span class="p">);</span></div><div class='line' id='LC124'>	<span class="k">auto</span> <span class="n">polygonFixture</span> <span class="o">=</span> <span class="n">polygonBody</span><span class="o">-&gt;</span><span class="n">CreateFixture</span><span class="p">(</span><span class="n">polygonShape</span><span class="p">.</span><span class="n">get</span><span class="p">(),</span> <span class="mf">0.0f</span><span class="p">);</span></div><div class='line' id='LC125'>	<span class="n">filter</span><span class="p">.</span><span class="n">categoryBits</span> <span class="o">=</span> <span class="n">Shape</span><span class="o">::</span><span class="n">destructible</span><span class="p">;</span></div><div class='line' id='LC126'>	<span class="n">polygonFixture</span><span class="o">-&gt;</span><span class="n">SetFilterData</span><span class="p">(</span><span class="n">filter</span><span class="p">);</span></div><div class='line' id='LC127'><span class="p">}</span></div><div class='line' id='LC128'><br/></div><div class='line' id='LC129'><span class="kt">void</span> <span class="n">drawMouseIndicator</span><span class="p">(</span><span class="n">sf</span><span class="o">::</span><span class="n">Vector2f</span> <span class="n">position</span><span class="p">,</span> <span class="kt">float</span> <span class="n">radius</span><span class="p">,</span> <span class="n">sf</span><span class="o">::</span><span class="n">RenderWindow</span><span class="o">&amp;</span> <span class="n">window</span><span class="p">)</span></div><div class='line' id='LC130'><span class="p">{</span></div><div class='line' id='LC131'>	<span class="n">sf</span><span class="o">::</span><span class="n">CircleShape</span> <span class="n">indicator</span><span class="p">;</span></div><div class='line' id='LC132'>	<span class="k">auto</span> <span class="n">circlePos</span> <span class="o">=</span> <span class="n">sf</span><span class="o">::</span><span class="n">Vector2f</span><span class="p">{</span> <span class="n">position</span><span class="p">.</span><span class="n">x</span> <span class="o">-</span> <span class="n">radius</span><span class="p">,</span> <span class="n">position</span><span class="p">.</span><span class="n">y</span> <span class="o">-</span> <span class="n">radius</span> <span class="p">};</span></div><div class='line' id='LC133'>	<span class="n">indicator</span><span class="p">.</span><span class="n">setPosition</span><span class="p">(</span><span class="n">circlePos</span><span class="p">);</span></div><div class='line' id='LC134'>	<span class="n">indicator</span><span class="p">.</span><span class="n">setOutlineThickness</span><span class="p">(</span><span class="mf">1.f</span><span class="p">);</span></div><div class='line' id='LC135'>	<span class="n">indicator</span><span class="p">.</span><span class="n">setFillColor</span><span class="p">(</span><span class="n">sf</span><span class="o">::</span><span class="n">Color</span><span class="p">{</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span> <span class="p">});</span></div><div class='line' id='LC136'>	<span class="n">indicator</span><span class="p">.</span><span class="n">setRadius</span><span class="p">(</span><span class="n">radius</span><span class="p">);</span></div><div class='line' id='LC137'>	<span class="n">window</span><span class="p">.</span><span class="n">draw</span><span class="p">(</span><span class="n">indicator</span><span class="p">);</span></div><div class='line' id='LC138'><span class="p">}</span></div><div class='line' id='LC139'><br/></div><div class='line' id='LC140'><span class="n">std</span><span class="o">::</span><span class="n">unordered_set</span><span class="o">&lt;</span><span class="n">b2Body</span><span class="o">*&gt;</span> <span class="n">queryDestructibleBodies</span><span class="p">(</span><span class="n">b2Vec2</span> <span class="n">position</span><span class="p">,</span> <span class="kt">float</span> <span class="n">radius</span><span class="p">,</span> <span class="k">const</span> <span class="n">b2World</span><span class="o">&amp;</span> <span class="n">world</span><span class="p">)</span></div><div class='line' id='LC141'><span class="p">{</span></div><div class='line' id='LC142'>	<span class="n">WorldQueryCallback</span> <span class="n">callback</span><span class="p">{</span> <span class="n">b2Shape</span><span class="o">::</span><span class="n">e_chain</span><span class="p">,</span> <span class="n">Shape</span><span class="o">::</span><span class="n">destructible</span> <span class="p">};</span></div><div class='line' id='LC143'>	<span class="n">b2AABB</span> <span class="n">aabb</span><span class="p">;</span></div><div class='line' id='LC144'>	<span class="n">aabb</span><span class="p">.</span><span class="n">lowerBound</span> <span class="o">=</span> <span class="p">{</span> <span class="n">position</span><span class="p">.</span><span class="n">x</span> <span class="o">-</span> <span class="n">radius</span><span class="p">,</span> <span class="n">position</span><span class="p">.</span><span class="n">y</span> <span class="o">-</span> <span class="n">radius</span> <span class="p">};</span></div><div class='line' id='LC145'>	<span class="n">aabb</span><span class="p">.</span><span class="n">upperBound</span> <span class="o">=</span> <span class="p">{</span> <span class="n">position</span><span class="p">.</span><span class="n">x</span> <span class="o">+</span> <span class="n">radius</span><span class="p">,</span> <span class="n">position</span><span class="p">.</span><span class="n">y</span> <span class="o">+</span> <span class="n">radius</span> <span class="p">};</span></div><div class='line' id='LC146'><br/></div><div class='line' id='LC147'>	<span class="n">world</span><span class="p">.</span><span class="n">QueryAABB</span><span class="p">(</span><span class="o">&amp;</span><span class="n">callback</span><span class="p">,</span> <span class="n">aabb</span><span class="p">);</span></div><div class='line' id='LC148'><br/></div><div class='line' id='LC149'>	<span class="k">return</span> <span class="n">callback</span><span class="p">.</span><span class="n">foundBodies</span><span class="p">;</span></div><div class='line' id='LC150'><span class="p">}</span></div><div class='line' id='LC151'><br/></div><div class='line' id='LC152'><span class="k">template</span><span class="o">&lt;</span><span class="k">typename</span> <span class="n">It</span><span class="o">&gt;</span></div><div class='line' id='LC153'><span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="kt">match_t</span><span class="o">&gt;</span> <span class="n">matchBodiesToRings</span><span class="p">(</span><span class="n">It</span> <span class="n">begin</span><span class="p">,</span> <span class="n">It</span> <span class="n">end</span><span class="p">)</span></div><div class='line' id='LC154'><span class="p">{</span></div><div class='line' id='LC155'>	<span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="kt">match_t</span><span class="o">&gt;</span> <span class="n">batch</span><span class="p">;</span></div><div class='line' id='LC156'><br/></div><div class='line' id='LC157'>	<span class="n">std</span><span class="o">::</span><span class="n">transform</span><span class="p">(</span><span class="n">begin</span><span class="p">,</span> <span class="n">end</span><span class="p">,</span> <span class="n">std</span><span class="o">::</span><span class="n">back_inserter</span><span class="p">(</span><span class="n">batch</span><span class="p">),</span> <span class="p">[](</span><span class="n">b2Body</span><span class="o">*</span> <span class="n">body</span><span class="p">)</span></div><div class='line' id='LC158'>	<span class="p">{</span></div><div class='line' id='LC159'>		<span class="k">auto</span> <span class="n">f</span> <span class="o">=</span> <span class="n">body</span><span class="o">-&gt;</span><span class="n">GetFixtureList</span><span class="p">();</span></div><div class='line' id='LC160'>		<span class="k">auto</span> <span class="n">shape</span> <span class="o">=</span> <span class="k">static_cast</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">*&gt;</span><span class="p">(</span><span class="n">f</span><span class="o">-&gt;</span><span class="n">GetShape</span><span class="p">());</span></div><div class='line' id='LC161'>		<span class="k">return</span> <span class="n">std</span><span class="o">::</span><span class="n">make_pair</span><span class="p">(</span><span class="n">body</span><span class="p">,</span> <span class="n">convertShape</span><span class="p">(</span><span class="n">body</span><span class="o">-&gt;</span><span class="n">GetWorldCenter</span><span class="p">(),</span> <span class="n">shape</span><span class="p">));</span></div><div class='line' id='LC162'>	<span class="p">});</span></div><div class='line' id='LC163'><br/></div><div class='line' id='LC164'>	<span class="k">return</span> <span class="n">batch</span><span class="p">;</span></div><div class='line' id='LC165'><span class="p">}</span></div><div class='line' id='LC166'><br/></div><div class='line' id='LC167'><span class="kt">void</span> <span class="n">processRemoval</span><span class="p">(</span><span class="n">b2Vec2</span> <span class="n">removalPosition</span><span class="p">,</span> <span class="kt">float</span> <span class="n">removalRadius</span><span class="p">,</span> <span class="n">b2World</span><span class="o">&amp;</span> <span class="n">world</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">simplifyGeometry</span><span class="p">)</span></div><div class='line' id='LC168'><span class="p">{</span></div><div class='line' id='LC169'>	<span class="k">auto</span> <span class="n">foundBodies</span> <span class="o">=</span> <span class="n">queryDestructibleBodies</span><span class="p">(</span><span class="n">removalPosition</span><span class="p">,</span> <span class="n">removalRadius</span><span class="p">,</span> <span class="n">world</span><span class="p">);</span></div><div class='line' id='LC170'>	<span class="k">auto</span> <span class="n">batch</span> <span class="o">=</span> <span class="n">matchBodiesToRings</span><span class="p">(</span><span class="n">foundBodies</span><span class="p">.</span><span class="n">begin</span><span class="p">(),</span> <span class="n">foundBodies</span><span class="p">.</span><span class="n">end</span><span class="p">());</span></div><div class='line' id='LC171'><br/></div><div class='line' id='LC172'>	<span class="c1">// Partition the shapes by area, so that elements to be processed are at the beginning</span></div><div class='line' id='LC173'>	<span class="k">auto</span> <span class="n">borderIt</span> <span class="o">=</span> <span class="n">std</span><span class="o">::</span><span class="n">partition</span><span class="p">(</span><span class="n">batch</span><span class="p">.</span><span class="n">begin</span><span class="p">(),</span> <span class="n">batch</span><span class="p">.</span><span class="n">end</span><span class="p">(),</span> <span class="p">[](</span><span class="k">const</span> <span class="kt">match_t</span><span class="o">&amp;</span> <span class="n">m</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC174'>		<span class="k">const</span> <span class="kt">double</span> <span class="n">areaEpsilon</span> <span class="o">=</span> <span class="mf">0.02</span><span class="p">;</span></div><div class='line' id='LC175'>		<span class="k">return</span> <span class="n">bg</span><span class="o">::</span><span class="n">area</span><span class="p">(</span><span class="n">m</span><span class="p">.</span><span class="n">second</span><span class="p">)</span> <span class="o">&gt;</span> <span class="n">areaEpsilon</span><span class="p">;</span></div><div class='line' id='LC176'>	<span class="p">});</span></div><div class='line' id='LC177'><br/></div><div class='line' id='LC178'>	<span class="c1">// Remove small shapes</span></div><div class='line' id='LC179'>	<span class="n">std</span><span class="o">::</span><span class="n">for_each</span><span class="p">(</span><span class="n">borderIt</span><span class="p">,</span> <span class="n">batch</span><span class="p">.</span><span class="n">end</span><span class="p">(),</span> <span class="p">[</span><span class="o">&amp;</span><span class="p">](</span><span class="k">const</span> <span class="kt">match_t</span><span class="o">&amp;</span> <span class="n">m</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC180'>		<span class="n">world</span><span class="p">.</span><span class="n">DestroyBody</span><span class="p">(</span><span class="n">m</span><span class="p">.</span><span class="n">first</span><span class="p">);</span></div><div class='line' id='LC181'>	<span class="p">});</span></div><div class='line' id='LC182'><br/></div><div class='line' id='LC183'>	<span class="c1">// Subtract the input polygon from each shape returned from the query</span></div><div class='line' id='LC184'>	<span class="kt">ring_t</span> <span class="n">diff</span> <span class="o">=</span> <span class="n">makeConvexRing</span><span class="p">(</span><span class="n">removalPosition</span><span class="p">,</span> <span class="n">removalRadius</span><span class="p">,</span> <span class="mi">16</span><span class="p">);</span></div><div class='line' id='LC185'>	<span class="n">boost</span><span class="o">::</span><span class="n">geometry</span><span class="o">::</span><span class="n">correct</span><span class="p">(</span><span class="n">diff</span><span class="p">);</span></div><div class='line' id='LC186'><br/></div><div class='line' id='LC187'>	<span class="k">typedef</span> <span class="n">std</span><span class="o">::</span><span class="n">pair</span><span class="o">&lt;</span><span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">&gt;</span><span class="p">,</span> <span class="n">b2Filter</span><span class="o">&gt;</span> <span class="kt">shape_property_t</span><span class="p">;</span></div><div class='line' id='LC188'>	<span class="n">std</span><span class="o">::</span><span class="n">vector</span><span class="o">&lt;</span><span class="kt">shape_property_t</span><span class="o">&gt;</span> <span class="n">resultShapes</span><span class="p">;</span></div><div class='line' id='LC189'>	<span class="n">std</span><span class="o">::</span><span class="n">for_each</span><span class="p">(</span><span class="n">batch</span><span class="p">.</span><span class="n">begin</span><span class="p">(),</span> <span class="n">borderIt</span><span class="p">,</span> <span class="p">[</span><span class="o">&amp;</span><span class="p">](</span><span class="k">const</span> <span class="kt">match_t</span><span class="o">&amp;</span> <span class="n">m</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC190'>		<span class="k">auto</span> <span class="n">subtractionResult</span> <span class="o">=</span> <span class="n">subtract</span><span class="p">(</span><span class="n">m</span><span class="p">.</span><span class="n">second</span><span class="p">,</span> <span class="n">diff</span><span class="p">);</span></div><div class='line' id='LC191'>		<span class="c1">// Simplify the results</span></div><div class='line' id='LC192'>		<span class="k">if</span> <span class="p">(</span><span class="n">simplifyGeometry</span><span class="p">)</span></div><div class='line' id='LC193'>		<span class="p">{</span></div><div class='line' id='LC194'>			<span class="n">simplify</span><span class="p">(</span><span class="n">subtractionResult</span><span class="p">);</span></div><div class='line' id='LC195'>		<span class="p">}</span></div><div class='line' id='LC196'><br/></div><div class='line' id='LC197'>		<span class="c1">// Convert the rings to b2ChainShapes and add to result shapes</span></div><div class='line' id='LC198'>		<span class="k">auto</span> <span class="n">converted</span> <span class="o">=</span> <span class="n">convertGeometry</span><span class="p">(</span><span class="n">subtractionResult</span><span class="p">);</span></div><div class='line' id='LC199'><br/></div><div class='line' id='LC200'>		<span class="k">auto</span> <span class="n">moveBegin</span> <span class="o">=</span> <span class="n">std</span><span class="o">::</span><span class="n">make_move_iterator</span><span class="p">(</span><span class="n">converted</span><span class="p">.</span><span class="n">begin</span><span class="p">());</span></div><div class='line' id='LC201'>		<span class="k">auto</span> <span class="n">moveEnd</span> <span class="o">=</span> <span class="n">std</span><span class="o">::</span><span class="n">make_move_iterator</span><span class="p">(</span><span class="n">converted</span><span class="p">.</span><span class="n">end</span><span class="p">());</span></div><div class='line' id='LC202'>		<span class="n">std</span><span class="o">::</span><span class="n">transform</span><span class="p">(</span><span class="n">moveBegin</span><span class="p">,</span> <span class="n">moveEnd</span><span class="p">,</span> <span class="n">std</span><span class="o">::</span><span class="n">back_inserter</span><span class="p">(</span><span class="n">resultShapes</span><span class="p">),</span></div><div class='line' id='LC203'>			<span class="p">[</span><span class="o">&amp;</span><span class="p">](</span><span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2ChainShape</span><span class="o">&gt;</span> <span class="n">converted</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC204'>			<span class="k">auto</span> <span class="n">filter</span> <span class="o">=</span> <span class="n">m</span><span class="p">.</span><span class="n">first</span><span class="o">-&gt;</span><span class="n">GetFixtureList</span><span class="p">()</span><span class="o">-&gt;</span><span class="n">GetFilterData</span><span class="p">();</span></div><div class='line' id='LC205'>			<span class="k">return</span> <span class="n">std</span><span class="o">::</span><span class="n">make_pair</span><span class="p">(</span><span class="n">std</span><span class="o">::</span><span class="n">move</span><span class="p">(</span><span class="n">converted</span><span class="p">),</span> <span class="n">filter</span><span class="p">);</span></div><div class='line' id='LC206'>		<span class="p">});</span></div><div class='line' id='LC207'><br/></div><div class='line' id='LC208'>		<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="n">subtractionResult</span><span class="p">.</span><span class="n">empty</span><span class="p">())</span></div><div class='line' id='LC209'>		<span class="p">{</span></div><div class='line' id='LC210'>			<span class="n">world</span><span class="p">.</span><span class="n">DestroyBody</span><span class="p">(</span><span class="n">m</span><span class="p">.</span><span class="n">first</span><span class="p">);</span></div><div class='line' id='LC211'>		<span class="p">}</span></div><div class='line' id='LC212'>	<span class="p">});</span></div><div class='line' id='LC213'><br/></div><div class='line' id='LC214'>	<span class="k">for</span> <span class="p">(</span><span class="k">auto</span><span class="o">&amp;&amp;</span> <span class="n">s</span> <span class="o">:</span> <span class="n">resultShapes</span><span class="p">)</span></div><div class='line' id='LC215'>	<span class="p">{</span></div><div class='line' id='LC216'>		<span class="n">b2BodyDef</span> <span class="n">bd</span><span class="p">;</span></div><div class='line' id='LC217'>		<span class="n">b2Body</span><span class="o">*</span> <span class="n">body</span> <span class="o">=</span> <span class="n">world</span><span class="p">.</span><span class="n">CreateBody</span><span class="p">(</span><span class="o">&amp;</span><span class="n">bd</span><span class="p">);</span></div><div class='line' id='LC218'>		<span class="k">auto</span> <span class="n">fixture</span> <span class="o">=</span> <span class="n">body</span><span class="o">-&gt;</span><span class="n">CreateFixture</span><span class="p">(</span><span class="n">s</span><span class="p">.</span><span class="n">first</span><span class="p">.</span><span class="n">get</span><span class="p">(),</span> <span class="mf">0.0f</span><span class="p">);</span></div><div class='line' id='LC219'>		<span class="n">fixture</span><span class="o">-&gt;</span><span class="n">SetFilterData</span><span class="p">(</span><span class="n">s</span><span class="p">.</span><span class="n">second</span><span class="p">);</span></div><div class='line' id='LC220'>	<span class="p">}</span></div><div class='line' id='LC221'><span class="p">}</span></div><div class='line' id='LC222'><br/></div><div class='line' id='LC223'><span class="kt">int</span> <span class="n">main</span><span class="p">()</span></div><div class='line' id='LC224'><span class="p">{</span></div><div class='line' id='LC225'>	<span class="n">sf</span><span class="o">::</span><span class="n">Font</span> <span class="n">font</span><span class="p">;</span></div><div class='line' id='LC226'>	<span class="n">sf</span><span class="o">::</span><span class="n">Text</span> <span class="n">overlayText</span><span class="p">;</span></div><div class='line' id='LC227'>	<span class="k">const</span> <span class="n">std</span><span class="o">::</span><span class="n">string</span> <span class="n">fontFile</span> <span class="o">=</span> <span class="s">&quot;am.ttf&quot;</span><span class="p">;</span></div><div class='line' id='LC228'>	<span class="k">if</span> <span class="p">(</span><span class="n">font</span><span class="p">.</span><span class="n">loadFromFile</span><span class="p">(</span><span class="n">fontFile</span><span class="p">))</span></div><div class='line' id='LC229'>	<span class="p">{</span></div><div class='line' id='LC230'>		<span class="n">overlayText</span><span class="p">.</span><span class="n">setFont</span><span class="p">(</span><span class="n">font</span><span class="p">);</span></div><div class='line' id='LC231'>	<span class="p">}</span></div><div class='line' id='LC232'>	<span class="k">else</span></div><div class='line' id='LC233'>	<span class="p">{</span></div><div class='line' id='LC234'>		<span class="n">std</span><span class="o">::</span><span class="n">cerr</span> <span class="o">&lt;&lt;</span> <span class="s">&quot;Could not find &quot;</span> <span class="o">&lt;&lt;</span> <span class="n">fontFile</span> <span class="o">&lt;&lt;</span> <span class="s">&quot;</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">;</span></div><div class='line' id='LC235'>		<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC236'>	<span class="p">}</span></div><div class='line' id='LC237'>	<span class="n">overlayText</span><span class="p">.</span><span class="n">setCharacterSize</span><span class="p">(</span><span class="mi">10</span><span class="p">);</span></div><div class='line' id='LC238'>	<span class="n">overlayText</span><span class="p">.</span><span class="n">setString</span><span class="p">(</span><span class="s">&quot;Hold left mouse button to modify</span><span class="se">\n</span><span class="s">Right mouse button to add objects&quot;</span><span class="p">);</span></div><div class='line' id='LC239'><br/></div><div class='line' id='LC240'>	<span class="n">sf</span><span class="o">::</span><span class="n">VideoMode</span> <span class="n">videoMode</span><span class="p">{</span> <span class="k">static_cast</span><span class="o">&lt;</span><span class="kt">unsigned</span> <span class="kt">int</span><span class="o">&gt;</span><span class="p">(</span><span class="n">screenWidth</span><span class="p">),</span></div><div class='line' id='LC241'>							 <span class="k">static_cast</span><span class="o">&lt;</span><span class="kt">unsigned</span> <span class="kt">int</span><span class="o">&gt;</span><span class="p">(</span><span class="n">screenHeight</span><span class="p">)</span> <span class="p">};</span></div><div class='line' id='LC242'><br/></div><div class='line' id='LC243'>	<span class="n">sf</span><span class="o">::</span><span class="n">ContextSettings</span> <span class="n">settings</span><span class="p">;</span></div><div class='line' id='LC244'>	<span class="n">settings</span><span class="p">.</span><span class="n">antialiasingLevel</span> <span class="o">=</span> <span class="mi">8</span><span class="p">;</span></div><div class='line' id='LC245'>	<span class="n">sf</span><span class="o">::</span><span class="n">RenderWindow</span> <span class="n">window</span><span class="p">(</span><span class="n">videoMode</span><span class="p">,</span> <span class="s">&quot;Box2D modifiable geometry&quot;</span><span class="p">,</span> <span class="n">sf</span><span class="o">::</span><span class="n">Style</span><span class="o">::</span><span class="n">Default</span><span class="p">,</span> <span class="n">settings</span><span class="p">);</span></div><div class='line' id='LC246'><br/></div><div class='line' id='LC247'>	<span class="n">std</span><span class="o">::</span><span class="n">unique_ptr</span><span class="o">&lt;</span><span class="n">b2World</span><span class="o">&gt;</span> <span class="n">physicsWorld</span><span class="p">{</span> <span class="k">new</span> <span class="n">b2World</span><span class="p">{</span> <span class="n">b2Vec2</span><span class="p">{</span> <span class="mf">0.0f</span><span class="p">,</span> <span class="mf">18.0f</span> <span class="p">}</span> <span class="p">}</span> <span class="p">};</span></div><div class='line' id='LC248'>	<span class="n">physicsWorld</span><span class="o">-&gt;</span><span class="n">SetAutoClearForces</span><span class="p">(</span><span class="nb">false</span><span class="p">);</span></div><div class='line' id='LC249'>	<span class="n">physicsWorld</span><span class="o">-&gt;</span><span class="n">SetContactListener</span><span class="p">(</span><span class="n">nullptr</span><span class="p">);</span></div><div class='line' id='LC250'>	<span class="n">DebugDraw</span> <span class="nf">debugDraw</span><span class="p">(</span><span class="o">&amp;</span><span class="n">window</span><span class="p">,</span> <span class="n">physicsWorld</span><span class="p">.</span><span class="n">get</span><span class="p">());</span></div><div class='line' id='LC251'><br/></div><div class='line' id='LC252'>	<span class="n">addStaticShapes</span><span class="p">(</span><span class="o">*</span><span class="n">physicsWorld</span><span class="p">);</span></div><div class='line' id='LC253'><br/></div><div class='line' id='LC254'>	<span class="n">sf</span><span class="o">::</span><span class="n">Clock</span> <span class="n">clock</span><span class="p">;</span></div><div class='line' id='LC255'><br/></div><div class='line' id='LC256'>	<span class="kt">bool</span> <span class="n">simplifyGeometry</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC257'>	<span class="k">while</span> <span class="p">(</span><span class="n">window</span><span class="p">.</span><span class="n">isOpen</span><span class="p">())</span></div><div class='line' id='LC258'>	<span class="p">{</span></div><div class='line' id='LC259'>		<span class="kt">float</span> <span class="n">elapsed</span> <span class="o">=</span> <span class="n">clock</span><span class="p">.</span><span class="n">restart</span><span class="p">().</span><span class="n">asSeconds</span><span class="p">();</span></div><div class='line' id='LC260'>		<span class="n">sf</span><span class="o">::</span><span class="n">Event</span> <span class="n">event</span><span class="p">;</span></div><div class='line' id='LC261'><br/></div><div class='line' id='LC262'>		<span class="k">auto</span> <span class="n">mousePos</span> <span class="o">=</span> <span class="n">sf</span><span class="o">::</span><span class="n">Mouse</span><span class="o">::</span><span class="n">getPosition</span><span class="p">(</span><span class="n">window</span><span class="p">);</span></div><div class='line' id='LC263'>		<span class="k">auto</span> <span class="n">worldPos</span> <span class="o">=</span> <span class="n">window</span><span class="p">.</span><span class="n">mapPixelToCoords</span><span class="p">(</span><span class="n">mousePos</span><span class="p">);</span></div><div class='line' id='LC264'>		<span class="k">const</span> <span class="kt">float</span> <span class="n">removalRadius</span> <span class="o">=</span> <span class="mf">25.f</span><span class="p">;</span></div><div class='line' id='LC265'>		<span class="n">b2Vec2</span> <span class="n">position</span> <span class="o">=</span> <span class="p">{</span> <span class="n">worldPos</span><span class="p">.</span><span class="n">x</span><span class="p">,</span> <span class="n">worldPos</span><span class="p">.</span><span class="n">y</span> <span class="p">};</span></div><div class='line' id='LC266'><br/></div><div class='line' id='LC267'>		<span class="k">while</span> <span class="p">(</span><span class="n">window</span><span class="p">.</span><span class="n">pollEvent</span><span class="p">(</span><span class="n">event</span><span class="p">))</span></div><div class='line' id='LC268'>		<span class="p">{</span></div><div class='line' id='LC269'>			<span class="k">if</span> <span class="p">(</span><span class="n">event</span><span class="p">.</span><span class="n">type</span> <span class="o">==</span> <span class="n">sf</span><span class="o">::</span><span class="n">Event</span><span class="o">::</span><span class="n">Closed</span><span class="p">)</span></div><div class='line' id='LC270'>			<span class="p">{</span></div><div class='line' id='LC271'>				<span class="n">window</span><span class="p">.</span><span class="n">close</span><span class="p">();</span></div><div class='line' id='LC272'>			<span class="p">}</span></div><div class='line' id='LC273'>			<span class="k">if</span> <span class="p">(</span><span class="n">event</span><span class="p">.</span><span class="n">type</span> <span class="o">==</span> <span class="n">sf</span><span class="o">::</span><span class="n">Event</span><span class="o">::</span><span class="n">MouseButtonPressed</span> <span class="o">&amp;&amp;</span> </div><div class='line' id='LC274'>				<span class="n">event</span><span class="p">.</span><span class="n">mouseButton</span><span class="p">.</span><span class="n">button</span> <span class="o">==</span> <span class="n">sf</span><span class="o">::</span><span class="n">Mouse</span><span class="o">::</span><span class="n">Button</span><span class="o">::</span><span class="n">Right</span><span class="p">)</span></div><div class='line' id='LC275'>			<span class="p">{</span></div><div class='line' id='LC276'>				<span class="n">ShapeFactory</span> <span class="n">factory</span><span class="p">{</span> <span class="n">constants</span><span class="o">::</span><span class="n">RENDER_SCALE</span> <span class="p">};</span></div><div class='line' id='LC277'>				<span class="k">auto</span> <span class="n">ballShape</span> <span class="o">=</span> <span class="n">factory</span><span class="p">.</span><span class="n">circle</span><span class="p">(</span><span class="n">position</span><span class="p">,</span> <span class="n">removalRadius</span> <span class="o">/</span> <span class="mf">2.f</span><span class="p">);</span></div><div class='line' id='LC278'>				<span class="n">b2BodyDef</span> <span class="n">ballDef</span><span class="p">;</span></div><div class='line' id='LC279'>				<span class="n">b2Body</span><span class="o">*</span> <span class="n">ballBody</span> <span class="o">=</span> <span class="n">physicsWorld</span><span class="o">-&gt;</span><span class="n">CreateBody</span><span class="p">(</span><span class="o">&amp;</span><span class="n">ballDef</span><span class="p">);</span></div><div class='line' id='LC280'>				<span class="k">auto</span> <span class="n">ballFixture</span> <span class="o">=</span> <span class="n">ballBody</span><span class="o">-&gt;</span><span class="n">CreateFixture</span><span class="p">(</span><span class="n">ballShape</span><span class="p">.</span><span class="n">get</span><span class="p">(),</span> <span class="mf">0.0f</span><span class="p">);</span></div><div class='line' id='LC281'>				<span class="n">ballBody</span><span class="o">-&gt;</span><span class="n">SetType</span><span class="p">(</span><span class="n">b2BodyType</span><span class="o">::</span><span class="n">b2_dynamicBody</span><span class="p">);</span></div><div class='line' id='LC282'>				<span class="k">auto</span> <span class="n">filter</span> <span class="o">=</span> <span class="n">ballFixture</span><span class="o">-&gt;</span><span class="n">GetFilterData</span><span class="p">();</span></div><div class='line' id='LC283'>				<span class="n">filter</span><span class="p">.</span><span class="n">categoryBits</span> <span class="o">=</span> <span class="n">Shape</span><span class="o">::</span><span class="n">normal</span><span class="p">;</span></div><div class='line' id='LC284'>				<span class="n">filter</span><span class="p">.</span><span class="n">maskBits</span> <span class="o">=</span> <span class="n">Shape</span><span class="o">::</span><span class="n">normal</span> <span class="o">|</span> <span class="n">Shape</span><span class="o">::</span><span class="n">destructible</span><span class="p">;</span></div><div class='line' id='LC285'>				<span class="n">ballFixture</span><span class="o">-&gt;</span><span class="n">SetFilterData</span><span class="p">(</span><span class="n">filter</span><span class="p">);</span></div><div class='line' id='LC286'>			<span class="p">}</span></div><div class='line' id='LC287'>			<span class="k">if</span> <span class="p">(</span><span class="n">event</span><span class="p">.</span><span class="n">type</span> <span class="o">==</span> <span class="n">sf</span><span class="o">::</span><span class="n">Event</span><span class="o">::</span><span class="n">KeyReleased</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC288'>				<span class="n">event</span><span class="p">.</span><span class="n">key</span><span class="p">.</span><span class="n">code</span> <span class="o">==</span> <span class="n">sf</span><span class="o">::</span><span class="n">Keyboard</span><span class="o">::</span><span class="n">S</span><span class="p">)</span></div><div class='line' id='LC289'>			<span class="p">{</span></div><div class='line' id='LC290'>				<span class="n">simplifyGeometry</span> <span class="o">=</span> <span class="o">!</span><span class="n">simplifyGeometry</span><span class="p">;</span></div><div class='line' id='LC291'>			<span class="p">}</span></div><div class='line' id='LC292'>		<span class="p">}</span></div><div class='line' id='LC293'><br/></div><div class='line' id='LC294'>		<span class="n">window</span><span class="p">.</span><span class="n">clear</span><span class="p">();</span></div><div class='line' id='LC295'><br/></div><div class='line' id='LC296'>		<span class="n">step</span><span class="p">(</span><span class="o">*</span><span class="n">physicsWorld</span><span class="p">,</span> <span class="n">elapsed</span><span class="p">);</span></div><div class='line' id='LC297'><br/></div><div class='line' id='LC298'>		<span class="n">b2Vec2</span> <span class="n">scaledPos</span> <span class="o">=</span> <span class="n">position</span><span class="p">;</span></div><div class='line' id='LC299'>		<span class="n">scaledPos</span> <span class="o">*=</span> <span class="p">(</span><span class="mf">1.f</span> <span class="o">/</span> <span class="n">constants</span><span class="o">::</span><span class="n">RENDER_SCALE</span><span class="p">);</span></div><div class='line' id='LC300'>		<span class="kt">float</span> <span class="n">scaledRadius</span> <span class="o">=</span> <span class="n">removalRadius</span> <span class="o">/</span> <span class="n">constants</span><span class="o">::</span><span class="n">RENDER_SCALE</span><span class="p">;</span></div><div class='line' id='LC301'><br/></div><div class='line' id='LC302'>		<span class="k">if</span> <span class="p">(</span><span class="n">sf</span><span class="o">::</span><span class="n">Mouse</span><span class="o">::</span><span class="n">isButtonPressed</span><span class="p">(</span><span class="n">sf</span><span class="o">::</span><span class="n">Mouse</span><span class="o">::</span><span class="n">Button</span><span class="o">::</span><span class="n">Left</span><span class="p">))</span></div><div class='line' id='LC303'>		<span class="p">{</span></div><div class='line' id='LC304'>			<span class="n">processRemoval</span><span class="p">(</span><span class="n">scaledPos</span><span class="p">,</span> <span class="n">scaledRadius</span><span class="p">,</span> <span class="o">*</span><span class="n">physicsWorld</span><span class="p">,</span> <span class="n">simplifyGeometry</span><span class="p">);</span></div><div class='line' id='LC305'>			<span class="n">drawMouseIndicator</span><span class="p">(</span><span class="n">worldPos</span><span class="p">,</span> <span class="n">removalRadius</span><span class="p">,</span> <span class="n">window</span><span class="p">);</span></div><div class='line' id='LC306'>		<span class="p">}</span></div><div class='line' id='LC307'><br/></div><div class='line' id='LC308'>		<span class="n">physicsWorld</span><span class="o">-&gt;</span><span class="n">DrawDebugData</span><span class="p">();</span></div><div class='line' id='LC309'>		<span class="n">window</span><span class="p">.</span><span class="n">draw</span><span class="p">(</span><span class="n">overlayText</span><span class="p">);</span></div><div class='line' id='LC310'>		<span class="n">window</span><span class="p">.</span><span class="n">display</span><span class="p">();</span></div><div class='line' id='LC311'>	<span class="p">}</span></div><div class='line' id='LC312'>	<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC313'><span class="p">}</span></div></pre></div></td>
         </tr>
       </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github" title="GitHub"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2014 <span title="0.02965s from github-fe123-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="fullscreen-contents js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped tooltipped-w" aria-label="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped tooltipped-w"
      aria-label="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-x close js-ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>


      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/frameworks-5bef6dacd990ce272ec009917ceea0b9d96f84b7.js" type="text/javascript"></script>
      <script async="async" crossorigin="anonymous" src="https://assets-cdn.github.com/assets/github-b34ff5b5950e79300fa8719b7d4a66b0d8723688.js" type="text/javascript"></script>
      
      
  </body>
</html>

